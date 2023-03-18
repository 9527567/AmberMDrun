import argparse
from . import pyamber
from . import equil
from . import mmpbsa


def arg_parse():
    parser = argparse.ArgumentParser(description='Demo of AmberMD')
    parser.add_argument('--parm7', '-p', type=str,
                        required=True, help="amber top file")
    parser.add_argument('--rst7', '-c', type=str,
                        required=True, help='amber rst file')
    parser.add_argument('--temp', '-t', type=float,
                        required=False, help='Temperature', default=298.15)
    parser.add_argument("--ns", '-n', type=int,
                        help="time for MD(ns)", default=100)
    parser.add_argument('--addmask', default=None,
                        type=str, help="add restarint mask")
    parser.add_argument("--gamd", type=bool, default=False, help="if run gamd")
    args = parser.parse_args()
    return args


def main():
    args = arg_parse()
    parm7 = args.parm7
    rst7 = args.rst7
    temp = args.temp
    gamd = args.gamd
    s = pyamber.SystemInfo(parm7, rst7)
    ns = args.ns
    if args.addmask is not None:
        heavymask = "\"" + s.getHeavyMask() + "|" + args.addmask + "\""
        backbonemask = "\"" + s.getBackBoneMask() + "|" + args.addmask + "\""
    else:
        heavymask = "\"" + s.getHeavyMask() + "\""
        backbonemask = "\"" + s.getBackBoneMask() + "\""
    rst7 = equil.prep(rst7=rst7, s=s, temp=temp, heavymask=heavymask,
                      backbonemask=backbonemask, loop=20)
    if gamd:
        md = pyamber.GaMd("GaMd", s, rst7, rst7, irest=True,
                          nscm=1000, nstlim=ns * 500000, ntwx=50000)
        md.Run()
    else:
        md = pyamber.NPT("Md", s, rst7, rst7, ntwx=50000, irest=True, nscm=1000, nstlim=ns * 500000)
        md.Run()


if __name__ == '__main__':
    main()
