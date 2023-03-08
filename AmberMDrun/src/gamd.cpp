//
// Created by jack on 2022-12-18.
//
#include "gamd.hpp"
#include "fmt/os.h"
GaMd::GaMd(const std::string &name, SystemInfo systemInfo, const std::string &rst7, const std::string &refc, bool irest, float temp, const std::string &restraintmask, float restraint_wt, int nstlim, float cut, int ntc, int ntf, float tautp, float taup, int mcbarint, float gamma_ln, float dt, int nscm, int ntwx, int ntpr, int ntwr, int igamd, int ie, int iep, int ied, int ntcmdprep, int ntcmd, int ntebprep, int nteb, int ntave, int irest_gamd, float sigma0P, float sigma0D, std::string timask1, std::string scmask1)
{
    ntb_ = 2;
    name_ = name;
    systemInfo_ = systemInfo;
    rst7_ = rst7;
    refc_ = refc;
    iRest_ = irest;
    restraintMask_ = restraintmask;
    restraint_wt_ = restraint_wt;
    cut_ = cut;
    temp_ = temp;
    nstLim_ = nstlim;
    tautp_ = tautp;
    taup_ = taup;
    mcbarint_ = mcbarint;
    gamma_ln_ = gamma_ln;
    dt_ = dt;
    nscm_ = nscm;
    nTwx_ = ntwx;
    nTpr_ = ntpr;
    nTwr_ = ntwr;
    ntc_ = ntc;
    ntf_ = ntf;
    ntpFlags_ = 1;
    if (systemInfo_.getnLipid() != 0 && systemInfo.getHasOrthoBox())
    {
        ntpFlags_ = 2;
    }
    if (iRest_)
    {
        ntx_ = 5;
    } else
    {
        ntx_ = 1;
    }
    igamd_ = igamd;
    ie_ = ie;
    iep_ = iep;
    ied_ = ied;
    ntcmdprep_ = ntcmdprep;
    nteb_ = nteb;
    ntave_ = ntave;
    irest_gamd_ = irest_gamd;
    sigma0P_ = sigma0P;
    sigma0D_ = sigma0D;
}
void GaMd::Run()
{
    Npt::Run();
}
GaMd *GaMd::setCut(float cut)
{
    return dynamic_cast<GaMd*>(Npt::setCut(cut));
}
GaMd *GaMd::setNTpr(int ntpr)
{
    return dynamic_cast<GaMd*>(Npt::setNTpr(ntpr));
}
GaMd *GaMd::setNTwx(int ntwx)
{
    return dynamic_cast<GaMd*>(Npt::setNTwx(ntwx));
}
GaMd *GaMd::setNTwr(int ntwr)
{
    return dynamic_cast<GaMd*>(Npt::setNTwr(ntwr));
}
GaMd *GaMd::setNstLim(int nstlim)
{
    return dynamic_cast<GaMd*>(Npt::setNstLim(nstlim));
}
GaMd *GaMd::setIrest(bool irest)
{
    return dynamic_cast<GaMd*>(Npt::setIrest(irest));
}
GaMd *GaMd::setTautp(float tautp)
{
    return dynamic_cast<GaMd*>(Npt::setTautp(tautp));
}
GaMd *GaMd::settaup(float taup)
{
    return dynamic_cast<GaMd*>(Npt::settaup(taup));
}
GaMd *GaMd::setMcbarint(int mcbarint)
{
    return dynamic_cast<GaMd*>(Npt::setMcbarint(mcbarint));
}
GaMd *GaMd::setGammaLn(float gamma_ln)
{
    return dynamic_cast<GaMd*>(Npt::setGammaLn(gamma_ln));
}
GaMd *GaMd::setDt(float dt)
{
    return dynamic_cast<GaMd*>(Npt::setDt(dt));
}
GaMd *GaMd::setNscm(int nscm)
{
    return dynamic_cast<GaMd*>(Npt::setNscm(nscm));
}
GaMd *GaMd::setNtx(int ntx)
{
    return dynamic_cast<GaMd*>(Npt::setNtx(ntx));
}
GaMd *GaMd::setNtc(int ntc)
{
    return dynamic_cast<GaMd*>(Npt::setNtc(ntc));
}
GaMd *GaMd::setNtf(int ntf)
{
    return dynamic_cast<GaMd*>(Npt::setNtf(ntf));
}
GaMd *GaMd::setTemp(float temp)
{
    return dynamic_cast<GaMd*>(Npt::setTemp(temp));
}
GaMd *GaMd::setBarostat(const std::string &baroType)
{
    return dynamic_cast<GaMd*>(Npt::setBarostat(baroType));
}
GaMd *GaMd::setThermostat(const std::string &thermoType)
{
    return dynamic_cast<GaMd*>(Npt::setThermostat(thermoType));
}
GaMd *GaMd::setRestraintMask(std::string restraintMask)
{
    return dynamic_cast<GaMd*>(Npt::setRestraintMask(restraintMask));
}
GaMd *GaMd::setRestraint_wt(float restraintMask)
{
    return dynamic_cast<GaMd*>(Npt::setRestraint_wt(restraintMask));
}
void GaMd::writeInput()
{
    Npt::writeInput();
    fmt::ostream out = fmt::output_file(name_ + ".in",fmt::file::WRONLY | fmt::file::APPEND);
    out.print("igamd={},",igamd_);
    out.print("ie={},",ie_);
    out.print("iep={},",iep_);
    out.print("ied={},",ied_);
    out.print("\n");
    out.print("ntcmdprep={},",ntcmdprep_);
    out.print("ntcmd={},",ntcmd_);
    out.print("ntebprep={},",ntebprep_);
    out.print("\n");
    out.print("nteb={},",nteb_);
    out.print("ntave={},",ntave_);
    out.print("\n");
    out.print("irest_gamd={},",irest_gamd_);
    out.print("sigma0P={},",sigma0P_);
    out.print("sigma0D={},",sigma0D_);
    out.print("\n");
    out.print("timask1={},",timask1_);
    out.print("scmask1={},",scmask1_);
    out.print("\n");
}
void GaMd::charmmWater()
{
    Npt::charmmWater();
}
void GaMd::restraint()
{
    Npt::restraint();
}
void GaMd::writeEnd()
{
    Npt::writeEnd();
}
void GaMd::runMd()
{
    Npt::runMd();
}
void GaMd::barostat()
{
    Npt::barostat();
}
void GaMd::Thermostat()
{
    Npt::Thermostat();
}
GaMd *GaMd::setIGaMd(int igamd)
{
    igamd_ = igamd;
    return this;
}
GaMd *GaMd::setIe(int ie)
{
    ie_ = ie;
    return this;
}
GaMd *GaMd::setIep(int iep)
{
    iep_ = iep;
    return this;
}
GaMd *GaMd::setIed(int ied)
{
    ied_ = ied;
    return this;
}
GaMd *GaMd::setNtcmdprep(int ntebprep)
{
    ntcmdprep_ = ntebprep;
    return this;
}
GaMd *GaMd::setNteb(int nteb)
{
    nteb_ = nteb;
    return this;
}
GaMd *GaMd::setNtave(int ntave)
{
    ntave_ = ntave;
    return this;
}
GaMd *GaMd::setIrest_gamd(int irest_gamd)
{
    irest_gamd_ = irest_gamd;
    return this;
}
GaMd *GaMd::setSigma0P(float sigma0P)
{
    sigma0P_ = sigma0P;
    return this;
}
GaMd *GaMd::setSigmaOD(float sigmaOD)
{
    sigma0D_ = sigmaOD;
    return this;
}
GaMd *GaMd::setTimask1(std::string timask)
{
    timask1_ = timask;
    return this;
}
GaMd *GaMd::setScmask1(std::string scmask)
{
    scmask1_ = scmask;
    return this;
}
