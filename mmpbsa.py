from pathlib import Path
import os
from main import prep
import argparse
import pyamber


def run_tleap(protein: str, mol: str):
    protein = Path(protein).absolute()
    mol = Path(mol).absolute()
    cmdline = f'pdb4amber -i {str(protein)} -o _{str(protein)} -y -d -p --add-missing-atoms'
    os.system(cmdline)
    cmdline = f'acpype -i {str(mol)}'
    os.system(cmdline)
    leapin = f"source leaprc.protein.ff14SB \
            source leaprc.DNA.OL15 \
            source leaprc.RNA.OL3 \
            source leaprc.water.tip3p \
            source leaprc.gaff2 \
            pro = loadpdb _{str(protein)} \
            loadamberparm {mol.stem}.acpype/{mol.stem}_AC.frcmod \
            mol = loadmol2 {str(mol)} \
            com = combine{{pro mol}} \
            solvatebox com TIP3PBOX 10.0 \
            addions2 com Na+ 0 \
            addions2 com Cl- 0 \
            saveamberparm com {protein.stem}_{mol.stem}.parm7 {protein.stem}_{mol.stem}.rst7        "
    return f'{protein.stem}_{mol.stem}.parm7' f'{protein.stem}_{mol.stem}.rst7'


def mmpbsa(parm7: str, rst7: str, netcdf: str, system: pyamber.SystemInfo):
    parm7 = Path(parm7).absolute()
    rst7 = Path(rst7).absolute()

    try:
        import parmed
    except:
        raise RuntimeError("you need to install parmed")
    amber_top = parmed.load_file(parm7, rst7)
    amber_top.save(str(parm7.with_suffix(".top")))
    cpptraj_in = f'parm {str(parm7)} \
                trajin {str(rst7)} \
                trajout {str(parm7.with_suffix(".top"))} \
                go \
                trajin {netcdf} \
                unwrap :1-{system.getNprotein()} \
                center :1-{system.getNprotein()} mass origin \
                image center origin familier \
                trajout {str(parm7.with_suffix(".xtc"))} \
                go \
                exit '
    with open("cpptraj.in", "w") as f:
        for i in cpptraj_in:
            f.write()
    os.system(f'cpptraj -i cpptraj.in')
    os.mkdir("MMPBSA")
    os.chdir("MMPBSA")
    from multiprocessing import cpu_count
    make_ndx = f'echo q | gmx make_ndx -f ../com.pdb -o index.ndx'
    os.system(make_ndx)
    mmpbsa_in = f'&general \
                startframe=12401,endframe=17601, verbose=2,interval=100, \
                / \
                &gb \
                igb=5, \
                / \
                &pb \
                istrng=0.1500,inp=1,stdiopt = 0 \
                /    \
                &decomp \
                idecomp=2, dec_verbose=3, \
                print_res="within 4" \
                /'
    with open("mmpbsa.in",'w') as f:
        for i in mmpbsa_in:
            f.write()
    mmpbsa = f"mpirun -np {cpu_count()} gmx_MMPBSA MPI -O -i mmpbsa.in -cs ../com.pdb -ci index.ndx -cg 1 13 -ct ../md.xtc  -cp \
    {str(parm7.with_suffix('top'))} -nogui"
    os.system(mmpbsa)


def arg_parse():
    parser = argparse.ArgumentParser(description='Demo of MMPBSA')
    parser.add_argument('--protein', '-p', type=str,
                        required=True, help="pdb file for protein")
    parser.add_argument('--mol2', '-m', type=str,
                        required=True, help='mol2 file for mol')
    parser.add_argument('--temp', '-t', type=float,
                        required=False, help='Temperature', default=303.15)
    parser.add_argument("--ns", '-n', type=int,
                        help="time for MD(ns)", default=100)
    parser.add_argument("--mmpbsa", type=bool,
                        default=True, help="if run mmpbsa")
    args = parser.parse_args()
    return args


def main():
    args = arg_parse()
    protein = args.pdb
    mol = args.mol2
    temp = args.temp
    mmpbsa = args.mmpbsa
    parm7, rst7 = run_tleap(protein, mol)
    s = pyamber.SystemInfo(parm7, rst7)
    heavymask = "\"" + s.getHeavyMask() + "\""
    backbonemask = "\"" + s.getBackBoneMask() + "\""
    prep(rst7=rst7, s=s, temp=temp, heavymask=heavymask,
         backbonemask=backbonemask, ns=100, gamd=False)
    if mmpbsa:
        mmpbsa(parm7,rst7,"md.nc",s)


if __name__ == '__main__':
    main()
