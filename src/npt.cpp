//
// Created by jack on 2022/12/7.
//
#include "npt.hpp"
#include <stdexcept>

Npt::Npt(const std::string &name, SystemInfo systemInfo, const std::string &rst7, const std::string &refc, bool irest, float temp, const std::string &restraintmask, float restraint_wt, int nstlim, float cut, int ntc, int ntf, float tautp, float taup, int mcbarint, float gamma_ln, float dt, int nscm, int ntwx, int ntpr, int ntwr)
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
}
void Npt::Run()
{
    Md::Run();
}
Npt *Npt::setCut(float cut)
{
    cut_ = cut;
    return this;
}
Npt *Npt::setNTpr(int ntpr)
{
    nTpr_ = ntpr;
    return this;
}
Npt *Npt::setNTwx(int ntwx)
{
    nTwx_ = ntwx;
    return this;
}
Npt *Npt::setNTwr(int ntwr)
{
    nTwr_ = ntwr;
    return this;
}
Npt *Npt::setNstLim(int nstlim)
{
    nstLim_ = nstlim;
    return this;
}
Npt *Npt::setIrest(bool irest)
{
    iRest_ = irest;
    if (iRest_)
    {
        ntx_ = 5;
    } else
    {
        ntx_ = 1;
    }
    return this;
}
Npt *Npt::setTautp(float tautp)
{
    tautp_ = tautp;
    return this;
}
Npt *Npt::settaup(float taup)
{
    taup_ = taup;
    return this;
}
Npt *Npt::setMcbarint(int mcbarint)
{
    mcbarint_ = mcbarint;
    return this;
}
Npt *Npt::setGammaLn(float gamma_ln)
{
    gamma_ln_ = gamma_ln;
    return this;
}
Npt *Npt::setDt(float dt)
{
    dt_ = dt;
    return this;
}
Npt *Npt::setNscm(int nscm)
{
    nscm_ = nscm;
    return this;
}
Npt *Npt::setNtx(int ntx)
{
    ntx_ = ntx;
    return this;
}
Npt *Npt::setNtc(int ntc)
{
    ntc_ = ntc;
    return this;
}
Npt *Npt::setNtf(int ntf)
{
    ntf_ = ntf;
    return this;
}
Npt *Npt::setBarostat(const std::string &baroType)
{
    if (baroType == "berendsen")
    {
        baroType_ = baro::berendsen;
    } else if (baroType == "montecarlo")
    {
        baroType_ = baro::montecarlo;
    } else
    {
        throw std::runtime_error("Baro type must be berendsen or montecarlo");
    }
    return this;
}
Npt *Npt::setThermostat(const std::string &thermoType)
{
    if (thermoType == "berendsen")
    {
        thermoType_ = thermo::berendsen;
    } else if (thermoType == "langevin")
    {
        thermoType_ = thermo::langevin;
    } else
    {
        throw std::runtime_error("Thermo type must be berendsen or langevin");
    }
    return this;
}
Npt *Npt::setTemp(float temp)
{
    temp_ = temp;
    return this;
}
void Npt::runMd()
{
    Md::runMd();
}
Npt *Npt::setRestraintMask(std::string restraintMask)
{
    restraintMask_ = std::move(restraintMask);
    return this;
}
void Npt::writeInput()
{
    Md::writeInput();
}
void Npt::charmmWater()
{
    Md::charmmWater();
}
void Npt::restraint()
{
    Md::restraint();
}
void Npt::writeEnd()
{
    Md::writeEnd();
}
void Npt::barostat()
{
    Md::barostat();
}
void Npt::Thermostat()
{
    Md::Thermostat();
}
Npt *Npt::setRestraint_wt(float restraint_wt)
{
    restraint_wt_ = restraint_wt;
    return this;
}
