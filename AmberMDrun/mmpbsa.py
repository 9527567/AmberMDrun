from pathlib import Path
import os
from .equil import prep
import argparse
from . import pyamber
import logging
from logging import getLogger
import subprocess
from typing import List


def runCMD(inCmd, *, raise_on_fail: bool = True, logger: logging.Logger = getLogger("mmpbsa"), **kwargs):
    p = subprocess.Popen(
        inCmd, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    output, error = p.communicate()
    p.wait()
    if p.returncode == 0:
        status = 'Success'
    else:
        status = 'Fail'
        logger.error(f'{inCmd} run failed')
        logger.debug(f'stdout:\n{output}')
        logger.debug(f'stderr:\n{error}')
        if raise_on_fail:
            if kwargs.get('message', None) is not None:
                raise RuntimeError(kwargs['message'])
            else:
                raise RuntimeError(f'{inCmd} run failed')
    return status, output, error


def split_pdb(pdb: str):
    try:
        import parmed as pd
        from pdb4amber.residue import (
            RESPROT, RESPROTE, RESNA,
            AMBER_SUPPORTED_RESNAMES,
            HEAVY_ATOM_DICT, RESSOLV)
    except:
        raise RuntimeError("you need to install parmed")
    com = pd.load_file(pdb)
    # remove water and ions
    water_mask = ':' + ','.join(RESSOLV)
    com.strip(water_mask)
    ns_names = list()
    for residue in com.residues:
        if len(residue.name) > 3:
            rname = residue.name[:3]
        else:
            rname = residue.name
        if rname.strip() not in AMBER_SUPPORTED_RESNAMES:
            logging.debug(f'ligand:{rname}')
            ns_names.append(rname)
            if len(ns_names) > 1:
                raise RuntimeError(
                    "Only a single ligand system is supported, or you can prepare your own system.")
    mol = com.copy(cls=pd.Structure)
    com.strip(f':{ns_names[0]}')
    com.write_pdb(f'pro.pdb')
    mol.strip(f"!:{ns_names[0]}")
    pd.formats.Mol2File.write(mol, "mol.mol2")
    return "pro.pdb", "mol.mol2"


def run_tleap(protein: str, mol_list: List, charge: List, multiplicity: List, guess_charge: bool):
    cmdline = f'pdb4amber -i {protein} -o _{str(protein)} -y -d -p'
    runCMD(cmdline)
    protein_path = Path(protein).absolute()
    mol_list = [Path(mol) for mol in mol_list]
    if guess_charge:
        for mol in mol_list:
            cmdline = f'acpype -i {str(Path(mol).absolute())}'
            runCMD(cmdline,
                   message="Perhaps you should check the charge of the ligand and the correctness of the hydrogen atom.")
    else:
        for mol, c, spin in zip(mol_list, charge, multiplicity):
            cmdline = f'acpype -i {str(Path(mol).absolute())} -n {c} -m {spin}'
            runCMD(cmdline,
                   message="Perhaps you should check the charge of the ligand and the correctness of the hydrogen atom.")

    mol_frcmod = f"".join(
        f'loadamberparams {mol_path.stem}.acpype/{mol_path.stem}_AC.frcmod\n' for mol_path in mol_list)
    mol_load = f"".join(
        f'{mol_path.stem} = loadmol2 {mol_path.stem}.acpype/{mol_path.stem}_bcc_gaff2.mol2\n' for mol_path in mol_list)
    combine = f'com = combine{{pro {" ".join(mol_path.stem for mol_path in mol_list)}}}\n'
    leapin = (f"""source leaprc.protein.ff14SB
source leaprc.DNA.OL15
source leaprc.RNA.OL3
source leaprc.water.tip3p
source leaprc.gaff2
pro = loadpdb _{protein}\n""") + mol_frcmod + mol_load + combine + (f"""solvatebox com TIP3PBOX 10.0
addionsrand com Na+ 0
addionsrand com Cl- 0
saveamberparm com com.parm7 com.rst7
quit""")
    with open("leap.in", "w") as f:
        for i in leapin:
            f.write(i)
    runCMD('tleap -f leap.in')
    return f'com.parm7', f'com.rst7'


def run_mmpbsa(parm7: str, rst7: str, netcdf: str, system: pyamber.SystemInfo, mol_list: List):
    parm7 = Path(parm7).absolute()
    rst7 = Path(rst7).absolute()

    try:
        import parmed
    except:
        raise RuntimeError("you need to install parmed")
    amber_top = parmed.load_file(str(parm7), str(rst7))
    if not parm7.with_suffix(".top").is_file():
        amber_top.save(str(parm7.with_suffix(".top")))
    cpptraj_in = f'parm {str(parm7)}\n \
trajin {str(rst7)}\n \
trajout {str(parm7.with_suffix(".pdb"))}\n \
go\n \
trajin {netcdf}\n \
unwrap :1-{system.getNprotein()}\n \
center :1-{system.getNprotein()} mass origin\n \
image center origin familiar\n \
trajout {str(parm7.with_suffix(".xtc"))}\n \
go\n \
exit '
    with open("cpptraj.in", "w") as f:
        for i in cpptraj_in:
            f.write(i)
    runCMD(f'cpptraj -i cpptraj.in')
    if not Path("MMPBSA").is_dir():
        Path("MMPBSA").mkdir()
    os.chdir("MMPBSA")
    from multiprocessing import cpu_count
    make_ndx = f"echo q | gmx make_ndx -f {str(parm7.with_suffix('.pdb'))} -o index.ndx"
    runCMD(make_ndx)
    mmpbsa_in = f'&general\n \
startframe=1, endframe=99999, verbose=2,interval=1,\n \
/\n \
&gb\n \
igb=5,\n \
/\n \
&pb\n \
istrng=0.1500,inp=1,radiopt = 0\n \
/\n    \
&decomp\n \
idecomp=2, dec_verbose=3,\n \
print_res="within 4"\n \
/'
    with open("mmpbsa.in", 'w') as f:
        for i in mmpbsa_in:
            f.write(i)
    mol_number = 13
    for mol in range(len(mol_list)):
        mol_path = Path.cwd().joinpath(f'lig{mol}')
        mol_path.mkdir(exist_ok=True)
        os.chdir(str(mol_path))
        mmpbsa = f"mpirun -np {cpu_count() // 2} gmx_MMPBSA MPI -O -i ../mmpbsa.in -cs {str(parm7.with_suffix('.pdb'))} -ci ../index.ndx -cg 1 {mol_number} -ct {str(parm7.with_suffix('.xtc'))}  -cp \
        {str(parm7.with_suffix('.top'))} -nogui"
        runCMD(mmpbsa)
        os.chdir('..')
        mol_number += 1


def arg_parse():
    parser = argparse.ArgumentParser(
        description='Tools for automating the operation of MMPBSA')
    parser.add_argument('--protein', '-p', type=str,
                        required=True, help="pdb file for protein")
    parser.add_argument('--mol2', '-m', type=str, nargs='+',
                        required=False, help='mol2 file for mol')
    parser.add_argument('--temp', '-t', type=float,
                        required=False, help='Temperature', default=303.15)
    parser.add_argument("--ns", '-n', type=int,
                        help="time for MD(ns)", default=100)
    parser.add_argument('-g', '--guess_charge',
                        action='store_true', help='guess charge')
    parser.add_argument('-c', "--charge", type=int, nargs='+',
                        default=[0], help="charge of mol")

    parser.add_argument("--multiplicity", type=int, nargs='+',
                        default=[1], help="multiplicity of mol")
    parser.add_argument("--MIN", type=str,
                        default="pmemd.cuda_DPFP", help="Engine for MIN")
    parser.add_argument("--MD", type=str,
                        default="pmemd.cuda", help="Engine for MD")
    args = parser.parse_args()
    return args


def mmpbsa():
    args = arg_parse()
    protein = args.protein
    mol_list = args.mol2
    temp = args.temp
    if not args.guess_charge:
        if len(mol_list) != len(args.charge) and len(mol_list) != len(args.multiplicity):
            raise ValueError(
                "If the charge is not guessed, it is necessary to specify the charge and spin multiplicity for each ligand.")

    if mol_list is None:
        protein, mol = split_pdb(protein)
        mol_list = [mol]
    parm7, rst7 = run_tleap(protein, mol_list, args.charge,
                            args.multiplicity, args.guess_charge)
    s = pyamber.SystemInfo(parm7, rst7, runMin=args.MIN, runMd=args.MD)
    heavymask = "\"" + s.getHeavyMask() + "\""
    backbonemask = "\"" + s.getBackBoneMask() + "\""
    rst7 = prep(rst7=rst7, s=s, temp=temp, heavymask=heavymask,
                backbonemask=backbonemask, loop=20)
    md = pyamber.NPT("md", s, rst7, rst7, ntwx=50000,
                     irest=True, nscm=1000, nstlim=args.ns * 500000)
    md.Run()
    rst7 = 'final_0.rst7'
    run_mmpbsa(parm7, rst7, "md.nc", s, mol_list)


if __name__ == '__main__':
    mmpbsa()
