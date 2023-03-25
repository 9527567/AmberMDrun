//
// Created by jack on 2022/12/7.
//
#include "nvt.hpp"
#include <stdexcept>
Nvt::Nvt(const std::string &name, SystemInfo systemInfo, const std::string &rst7, const std::string &refc, bool irest, float temp, const std::string &restraintmask, float restraint_wt, int nstlim, float cut, int ntc, int ntf, float gamma_ln,float tautp, float dt, int nscm, int ntwx, int ntpr, int ntwr)
{
    ntb_ = 1;
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
Nvt *Nvt::setCut(float cut)
{
    cut_ = cut;
    return this;
}
Nvt *Nvt::setNTpr(int ntpr)
{
    nTpr_ = ntpr;
    return this;
}
Nvt *Nvt::setNTwx(int ntwx)
{
    nTwx_ = ntwx;
    return this;
}
Nvt *Nvt::setNTwr(int ntwr)
{
    nTwr_ = ntwr;
    return this;
}
Nvt *Nvt::setNstLim(int nstlim)
{
    nstLim_ = nstlim;
    return this;
}
Nvt *Nvt::setIrest(bool irest)
{
    iRest_ = irest;
    return this;
}
Nvt *Nvt::setGammaLn(float gamma_ln)
{
    gamma_ln_ = gamma_ln;
    return this;
}
Nvt *Nvt::setDt(float dt)
{
    dt_ = dt;
    return this;
}
Nvt *Nvt::setNscm(int nscm)
{
    nscm_ = nscm;
    return this;
}
Nvt *Nvt::setNtx(int ntx)
{
    ntx_ = ntx;
    return this;
}
Nvt *Nvt::setNtc(int ntc)
{
    ntc_ = ntc;
    return this;
}
Nvt *Nvt::setNtf(int ntf)
{
    ntf_ = ntf;
    return this;
}
Nvt *Nvt::setTemp(float temp)
{
    temp_ = temp;
    return this;
}

Nvt *Nvt::setThermostat(const std::string &thermoType)
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
Nvt *Nvt::setRestraintMask(std::string restraintMask)
{
    restraintMask_ = std::move(restraintMask);
    return this;
}
void Nvt::writeInput()
{
    Md::writeInput();
}
void Nvt::charmmWater()
{
    Md::charmmWater();
}
void Nvt::restraint()
{
    Md::restraint();
}
void Nvt::writeEnd()
{
    Md::writeEnd();
}
void Nvt::runMd()
{
    Md::runMd();
}
void Nvt::Thermostat()
{
    Md::Thermostat();
}
void Nvt::Run()
{
    Md::Run();
}
Nvt *Nvt::setTautp(float tautp)
{
    tautp_ = tautp;
    return this;
}
Nvt *Nvt::setRestraint_wt(float restraint_wt)
{
    restraint_wt_ = restraint_wt;
    return this;
}
