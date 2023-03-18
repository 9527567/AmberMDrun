from . import _pyamber


class SystemInfo(_pyamber.SystemInfo):
    def __init__(self, parm7, rst7, runMin="pmemd.cuda_DPFP", runMd="pmemd.cuda") -> None:
        super().__init__(prmtop=parm7, inpcrd=rst7, runMin=runMin, runMd=runMd)

    getNprotein = _pyamber.SystemInfo.getNprotein
    getnDna = _pyamber.SystemInfo.getnDna
    getnRna = _pyamber.SystemInfo.getnRna
    getnLipid = _pyamber.SystemInfo.getnLipid
    getnUnKnown_ = _pyamber.SystemInfo.getnUnKnown_
    getnCharmmWater_ = _pyamber.SystemInfo.getnCharmmWater_
    getnWater = _pyamber.SystemInfo.getnWater
    getnCarbo = _pyamber.SystemInfo.getnCarbo
    getHasCharmmWater = _pyamber.SystemInfo.getHasCharmmWater
    getHasOrthoBox = _pyamber.SystemInfo.getHasOrthoBox
    getRunMin = _pyamber.SystemInfo.getRunMin
    getRunMd = _pyamber.SystemInfo.getRunMd
    getHeavyMask = _pyamber.SystemInfo.getHeavyMask
    getBackBoneMask = _pyamber.SystemInfo.getBackBoneMask


class Min(_pyamber.Min):
    def __init__(self, name, systemInfo, ref, refc,
                 irest=False, restraintmask="", restraint_wt=0.0, cut=8.0, nTmin=2, maxCyc=1000,
                 nCyc=10, nTwx=500, nTpr=50, nTwr=500) -> None:
        super().__init__(name, systemInfo, ref, refc, irest=irest, restraintmask=restraintmask,
                         restraint_wt=restraint_wt, cut=cut, nTmin=nTmin, maxCyc=maxCyc, nCyc=nCyc, nTwx=nTwx,
                         nTpr=nTpr, nTwr=nTwr)

    setCut = _pyamber.Min.setCut
    setNTpr = _pyamber.Min.setNTpr
    setNTwr = _pyamber.Min.setNTwr
    setNTwx = _pyamber.Min.setNTwx
    setMaxCyc = _pyamber.Min.setMaxCyc
    setNCyc = _pyamber.Min.setNCyc
    setNTim = _pyamber.Min.setNTim
    Run = _pyamber.Min.Run


class NVT(_pyamber.Nvt):
    def __init__(self, name, systemInfo, ref, refc,
                 irest=False, temp=303.15, restraintmask="", restraint_wt=0.0, nstlim=5000, cut=8.0, ntb=1,
                 ntc=2, ntf=2, tautp=1.0, gamma_ln=5.0, dt=0.002, nscm=0, ntwx=500, ntpr=50, ntwr=500) -> None:
        super().__init__(name, systemInfo, ref, refc, irest=irest, temp=temp, restraintmask=restraintmask,
                         restraint_wt=restraint_wt,
                         nstlim=nstlim, cut=cut, ntc=ntc, ntf=ntf, tautp=tautp, gamma_ln=gamma_ln, dt=dt, nscm=nscm,
                         ntwx=ntwx, ntpr=ntpr, ntwr=ntwr)

    Run = _pyamber.Nvt.Run
    setCut = _pyamber.Nvt.setCut
    setTemp = _pyamber.Nvt.setTemp
    setNTpr = _pyamber.Nvt.setNTpr
    setNTwx = _pyamber.Nvt.setNTwx
    setNTwr = _pyamber.Nvt.setNTwr
    setNstLim = _pyamber.Nvt.setNstLim
    setIrest = _pyamber.Nvt.setIrest
    setTautp = _pyamber.Nvt.setTautp
    setGammaLn = _pyamber.Nvt.setGammaLn
    setDt = _pyamber.Nvt.setDt
    setNscm = _pyamber.Nvt.setNscm
    setNtx = _pyamber.Nvt.setNtx
    setNtc = _pyamber.Nvt.setNtc
    setNtf = _pyamber.Nvt.setNtf
    setThermostat = _pyamber.Nvt.setThermostat


class NPT(_pyamber.Npt):
    def __init__(self, name, systemInfo, ref, refc,
                 irest=False, temp=303.15, restraintmask="", restraint_wt=0.0, nstlim=5000, cut=8.0, ntc=2, ntf=2,
                 tautp=1.0, taup=1.0, mcbarint=100, gamma_ln=5.0, dt=0.002, nscm=0, ntwx=500, ntpr=50,
                 ntwr=500) -> None:
        super().__init__(name, systemInfo, ref, refc, irest=irest, temp=temp, restraintmask=restraintmask,
                         restraint_wt=restraint_wt,
                         nstlim=nstlim, cut=cut, ntc=ntc, ntf=ntf, tautp=tautp, taup=taup, mcbarint=mcbarint,
                         gamma_ln=gamma_ln, dt=dt, nscm=nscm, ntwx=ntwx, ntpr=ntpr, ntwr=ntwr)

    Run = _pyamber.Npt.Run
    setCut = _pyamber.Npt.setCut
    setTemp = _pyamber.Npt.setTemp
    setNTpr = _pyamber.Npt.setNTpr
    setNTwx = _pyamber.Npt.setNTwx
    setNTwr = _pyamber.Npt.setNTwr
    setNstLim = _pyamber.Npt.setNstLim
    setIrest = _pyamber.Npt.setIrest
    setTautp = _pyamber.Npt.setTautp
    setTaup = _pyamber.Npt.setTaup
    setMcbarint = _pyamber.Npt.setMcbarint
    setGammaLn = _pyamber.Npt.setGammaLn
    setDt = _pyamber.Npt.setDt
    setNscm = _pyamber.Npt.setNscm
    setNtx = _pyamber.Npt.setNtx
    setNtc = _pyamber.Npt.setNtc
    setNtf = _pyamber.Npt.setNtf
    setThermostat = _pyamber.Npt.setThermostat


class GaMd(_pyamber.GaMd):
    def __init__(self, name, systemInfo, ref, refc,
                 irest=False, temp=303.15, restraintmask="", restraint_wt=0.0, nstlim=5000, cut=8.0, ntc=2, ntf=2,
                 tautp=1.0, taup=1.0, mcbarint=100, gamma_ln=5.0, dt=0.002, nscm=0, ntwx=500, ntpr=50, ntwr=500,
                 igamd=1, ie=1, iep=1, ied=1, ntcmdprep=200000, ntcmd=1000000, ntebprep=200000, nteb=1000000,
                 ntave=50000, irest_gamd=0, sigma0P=6.0, sigma0D=6.0, timask1="", scmask1="") -> None:
        super().__init__(name, systemInfo, ref, refc, irest=irest, temp=temp, restraintmask=restraintmask,
                         restraint_wt=restraint_wt,
                         nstlim=nstlim, cut=cut, ntc=ntc, ntf=ntf, tautp=tautp, taup=taup, mcbarint=mcbarint,
                         gamma_ln=gamma_ln, dt=dt, nscm=nscm, ntwx=ntwx, ntpr=ntpr, ntwr=ntwr,
                         igamd=igamd, ie=ie, iep=iep, ied=ied, ntcmdprep=ntcmdprep, ntcmd=ntcmd, ntebprep=ntebprep,
                         nteb=nteb, ntave=ntave, irest_gamd=irest_gamd, sigma0P=sigma0P, sigma0D=sigma0D,
                         timask1=timask1, scmask1=scmask1)

    Run = _pyamber.GaMd.Run
    setCut = _pyamber.GaMd.setCut
    setTemp = _pyamber.GaMd.setTemp
    setNTpr = _pyamber.GaMd.setNTpr
    setNTwx = _pyamber.GaMd.setNTwx
    setNTwr = _pyamber.GaMd.setNTwr
    setNstLim = _pyamber.GaMd.setNstLim
    setIrest = _pyamber.GaMd.setIrest
    setTautp = _pyamber.GaMd.setTautp
    setTaup = _pyamber.GaMd.setTaup
    setMcbarint = _pyamber.GaMd.setMcbarint
    setGammaLn = _pyamber.GaMd.setGammaLn
    setDt = _pyamber.GaMd.setDt
    setNscm = _pyamber.GaMd.setNscm
    setNtx = _pyamber.GaMd.setNtx
    setNtc = _pyamber.GaMd.setNtc
    setNtf = _pyamber.GaMd.setNtf
    setThermostat = _pyamber.GaMd.setThermostat
    setIGaMd = _pyamber.GaMd.setIGaMd
    setIe = _pyamber.GaMd.setIe
    setIep = _pyamber.GaMd.setIep
    setIed = _pyamber.GaMd.setIed
    setNtcmdprep = _pyamber.GaMd.setNtcmdprep
    setNteb = _pyamber.GaMd.setNteb
    setNtave = _pyamber.GaMd.setNtave
    setIrest_gamd = _pyamber.GaMd.setIrest_gamd
    setSigma0P = _pyamber.GaMd.setSigma0P
    setSigmaOD = _pyamber.GaMd.setSigmaOD
    setTimask1 = _pyamber.GaMd.setTimask1
    setTimask1 = _pyamber.GaMd.setTimask1
