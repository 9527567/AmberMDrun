import argparse
import pyamber


def arg_parse():
    parser = argparse.ArgumentParser(description='Demo of AmberMD')
    parser.add_argument('--parm7', '-p', type=str,
                        required=True, help="amber top file")
    parser.add_argument('--rst7', '-c', type=str,
                        required=True, help='amber rst file')
    parser.add_argument('--temp', '-t', type=float,
                        required=False, help='Temperature', default=303.15)
    parser.add_argument("--ns", '-n', type=int,
                        help="time for MD(ns)", default=100)
    parser.add_argument('--addmask', default=None,
                        type=str, help="add restarint mask")
    parser.add_argument("--gamd", type=bool, default=False, help="if run gamd")
    args = parser.parse_args()
    return args


def prep(rst7, s, temp, heavymask, backbonemask, ns, gamd):
    min1 = pyamber.Min("step1", systemInfo=s, ref=rst7,
                       refc=rst7, restraintmask=heavymask, restraint_wt=5.0)
    min1.Run()
    nvt1 = pyamber.NVT("step2", systemInfo=s, ref="step1.rst7", refc="step1.rst7", temp=temp,
                       restraintmask=heavymask, restraint_wt=5.0, nstlim=15000, tautp=0.5)
    nvt1.Run()
    min2 = pyamber.Min('step3', systemInfo=s, ref='step2.rst7',
                       refc='step2.rst7', restraintmask=heavymask, restraint_wt=2.0)
    min2.Run()
    min3 = pyamber.Min('step4', systemInfo=s, ref='step3.rst7',
                       refc='step3.rst7', restraintmask=backbonemask, restraint_wt=0.1)
    min3.Run()
    min4 = pyamber.Min('step5', systemInfo=s,
                       ref='step4.rst7', refc='step4.rst7')
    min4.Run()
    npt1 = pyamber.NPT("step6", systemInfo=s, ref="step5.rst7", temp=temp,
                       refc="step5.rst7", restraintmask=heavymask, restraint_wt=1.0)
    npt1.Run()
    npt2 = pyamber.NPT("step7", systemInfo=s, ref="step6.rst7", refc="step5.rst7", temp=temp,
                       irest=True, restraintmask=heavymask, restraint_wt=0.5)
    npt2.Run()
    npt3 = pyamber.NPT("step8", systemInfo=s, ref="step7.rst7", refc="step5.rst7", temp=temp,
                       irest=True, restraintmask=backbonemask, restraint_wt=0.5, nstlim=10000)
    npt3.Run()
    npt4 = pyamber.NPT("step9", systemInfo=s, ref="step8.rst7", temp=temp,
                       refc="step5.rst7", irest=True, dt=0.002, nscm=1000)
    npt4.Run()
    if gamd:
        gamd1 = pyamber.GaMd("GaMd1", systemInfo=s, ref="step9.rst7", temp=temp,
                             refc="step5.rst7", irest=True, dt=0.002, nscm=1000, nstlim=26000000, ntwx=50000, igamd=3, ie=1, irest_gamd=0,
                             ntcmd=1000000, nteb=25000000, ntave=200000,
                             ntcmdprep=200000, ntebprep=800000,
                             sigma0P=6.0, sigma0D=6.0)
        gamd1.Run()
        gamd2 = pyamber.GaMd("GaMd2", systemInfo=s, ref="GaMd1.rst7", temp=temp,
                             refc="GaMd1.rst7", irest=False, dt=0.002, nscm=1000, nstlim=50000000, ntwx=50000, igamd=3, iE=1, irest_gamd=1,
                             ntcmd=0, nteb=0, ntave=200000,
                             ntcmdprep=0, ntebprep=0,
                             sigma0P=6.0, sigma0D=6.0)
        gamd2.Run()
    else:
        md = pyamber.NPT("Md", systemInfo=s, ref="step9.rst7", temp=temp,
                         refc="step5.rst7", irest=True, dt=0.002, nscm=1000, nstlim=ns*500000, ntwx=50000)
        md.Run()


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
    prep(rst7=rst7, s=s, temp=temp, heavymask=heavymask,
         backbonemask=backbonemask, ns=ns, gamd=gamd)


if __name__ == '__main__':
    main()
