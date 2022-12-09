import _pyamber


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
    def __init__(self, name, systemInfo, ref, refc, irest=False, restraintmask="", restraint_wt=0.0, cut=8.0, nTmin=2, maxCyc=1000, nCyc=10, nTwx=500, nTpr=50, nTwr=500) -> None:
        super().__init__(name, systemInfo, ref, refc, irest=irest, restraintmask=restraintmask,
                         restraint_wt=restraint_wt, cut=cut, nTmin=nTmin, maxCyc=maxCyc, nCyc=nCyc, nTwx=nTwx, nTpr=nTpr, nTwr=nTwr)
    setCut = _pyamber.Min.setCut
    setNTpr = _pyamber.Min.setNTpr
    setNTwr = _pyamber.Min.setNTwr
    setNTwx = _pyamber.Min.setNTwx
    setMaxCyc = _pyamber.Min.setMaxCyc
    setNCyc = _pyamber.Min.setNCyc
    setNTim = _pyamber.Min.setNTim
    Run = _pyamber.Min.Run


class NVT(_pyamber.Nvt):
    def __init__(self, name, systemInfo, ref, refc, irest=False, temp=303.15, restraintmask="", restraint_wt=0.0, nstlim=5000, cut=8.0, ntb=1, ntc=2, ntf=2, tautp=1.0, gamma_ln=5.0, dt=0.002, nscm=0, ntwx=500, ntpr=50, ntwr=500) -> None:
        super().__init__(name, systemInfo, ref, refc, irest=irest, temp=temp, restraintmask=restraintmask, restraint_wt=restraint_wt,
                         nstlim=nstlim, cut=cut, ntc=ntc, ntf=ntf, tautp=tautp, gamma_ln=gamma_ln, dt=dt, nscm=nscm, ntwx=ntwx, ntpr=ntpr, ntwr=ntwr)
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
    def __init__(self, name, systemInfo, ref, refc, irest=False, temp=303.15, restraintmask="", restraint_wt=0.0, nstlim=5000, cut=8.0, ntc=2, ntf=2, tautp=1.0, taup=1.0, mcbarint=100, gamma_ln=5.0, dt=0.002, nscm=0, ntwx=500, ntpr=50, ntwr=500) -> None:
        super().__init__(name, systemInfo, ref, refc, irest=irest, temp=temp, restraintmask=restraintmask, restraint_wt=restraint_wt,
                         nstlim=nstlim, cut=cut, ntc=ntc, ntf=ntf, tautp=tautp, taup=taup, mcbarint=mcbarint, gamma_ln=gamma_ln, dt=dt, nscm=nscm, ntwx=ntwx, ntpr=ntpr, ntwr=ntwr)
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

