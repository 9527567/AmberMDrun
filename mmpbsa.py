from pathlib import Path
import os
from equil import prep
import argparse
import pyamber


def run_tleap(protein: str, mol: str):
    cmdline = f'pdb4amber -i {protein} -o _{str(protein)} -y -d -p'
    os.system(cmdline)
    protein_path = Path(protein).absolute()
    mol_path = Path(mol).absolute()
    cmdline = f'acpype -i {str(mol_path)}'
    os.system(cmdline)
    leapin = f"source leaprc.protein.ff14SB\n\
            source leaprc.DNA.OL15\n\
            source leaprc.RNA.OL3\n\
            source leaprc.water.tip3p\n\
            source leaprc.gaff2\n\
            pro = loadpdb _{protein}\n\
            loadamberparams {mol_path.stem}.acpype/{mol_path.stem}_AC.frcmod\n\
            mol = loadmol2 {mol_path.stem}.acpype/{mol_path.stem}_bcc_gaff2.mol2\n\
            com = combine{{pro mol}}\n\
            solvatebox com TIP3PBOX 10.0\n\
            addions2 com Na+ 0\n\
            addions2 com Cl- 0\n\
            saveamberparm com {protein_path.stem}_{mol_path.stem}.parm7 {protein_path.stem}_{mol_path.stem}.rst7\n\
            quit"
    with open("leap.in", "w") as f:
        for i in leapin:
            f.write(i)
    os.system('tleap -f leap.in')
    return f'{protein_path.stem}_{mol_path.stem}.parm7', f'{protein_path.stem}_{mol_path.stem}.rst7'


def mmpbsa(parm7: str, rst7: str, netcdf: str, system: pyamber.SystemInfo):
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
image center origin familier\n \
trajout {str(parm7.with_suffix(".xtc"))}\n \
go\n \
exit '
    with open("cpptraj.in", "w") as f:
        for i in cpptraj_in:
            f.write(i)
    os.system(f'cpptraj -i cpptraj.in')
    if not Path("MMPBSA").is_dir():
        Path("MMPBSA").mkdir()
    os.chdir("MMPBSA")
    from multiprocessing import cpu_count
    make_ndx = f"echo q | gmx make_ndx -f {str(parm7.with_suffix('.pdb'))} -o index.ndx"
    os.system(make_ndx)
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
    with open("mmpbsa.in",'w') as f:
        for i in mmpbsa_in:
            f.write(i)
    mmpbsa = f"mpirun -np {cpu_count()//2} gmx_MMPBSA MPI -O -i mmpbsa.in -cs {str(parm7.with_suffix('.pdb'))} -ci index.ndx -cg 1 13 -ct {str(parm7.with_suffix('.xtc'))}  -cp \
    {str(parm7.with_suffix('.top'))} -nogui"
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
    protein = args.protein
    mol = args.mol2
    temp = args.temp
    parm7, rst7 = run_tleap(protein, mol)
    s = pyamber.SystemInfo(parm7, rst7)
    heavymask = "\"" + s.getHeavyMask() + "\""
    backbonemask = "\"" + s.getBackBoneMask() + "\""
    rst7= prep(rst7=rst7, s=s, temp=temp, heavymask=heavymask,
         backbonemask=backbonemask,loop=20)
    md = pyamber.NPT("md", s, rst7, rst7, ntwx=50000, irest=True, nscm=1000, nstlim=args.ns*500000)
    md.Run()
    if args.mmpbsa:
        mmpbsa(parm7,rst7,"md.nc",s)


if __name__ == '__main__':
    main()
