import argparse
import pyamber
import os


def arg_parse():
    parser = argparse.ArgumentParser(description='Demo of AmberMD')
    parser.add_argument('--parm7', '-p', type=str,
                        required=True, help="amber top file")
    parser.add_argument('--rst7', '-c', type=str,
                        required=True, help='amber rst file')
    parser.add_argument('--temp', '-t', type=float,
                        required=True, help='Temperature')
    parser.add_argument('--overwrite', '-O', type=bool,
                        help='Overwrite existing files, otherwise skip.', default=True)
    parser.add_argument('--thermo', type=str, help='Thermostat',
                        choices=["berendsen", "langevin"], default="langevin")
    parser.add_argument('--baro', type=str, help='Barostat',
                        choices=["berendsen", "montecarlo"], default="montecarlo")
    parser.add_argument('--finalthermo', type=str, help='Final stage thermostat',
                        choices=["berendsen", "langevin"], default="langevin")
    parser.add_argument('--finalbaro', type=str, help='Final stage barostat',
                        choices=["berendsen", "langevin"], default="montecarlo")
    parser.add_argument(
        '--mask', type=str, help='Additional mask to use for restraints during steps 1-8.')
    parser.add_argument(
        '--pmask', help='Restraint mask to use during production (steps 9 and above).', type=str)
    parser.add_argument(
        '--pref', type=str, help='Optional reference structure to use for \'--pmask\'.')
    parser.add_argument('--charmmwater', type=str,
                        help='If specified assume CHARMM water (i.e. \'TIP3\').')
    parser.add_argument(
        '--cutoff', type=str, help='If specified, override default cutoffs with <cut>.')
    parser.add_argument('--norestart', type=str,
                        help='Do standard Eq with no restarts.')
    args = parser.parse_args()
    return args


def main():
    args = arg_parse()
    parm7 = args.parm7
    rst7 = args.rst7
    s = pyamber.SystemInfo(parm7, rst7)
    # min1 = pyamber.Min("step1",systemInfo=s,ref="com.rst7",refc="com.rst7",restraint_wt=5.0)
    # min1.Run()
    # nvt1 = pyamber.NVT("step2",systemInfo=s,ref="step1.rst7",refc="step1.rst7",restraint_wt=2.0)
    # nvt1.Run()
    npt1 = pyamber.NPT("step3",systemInfo=s,ref="step2.rst7",refc="step2.rst7",irest=True)
    npt1.Run()
if __name__ == '__main__':
    main()
