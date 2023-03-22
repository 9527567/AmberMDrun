//
// Created by jack on 3/3/23.
//
#include "smd.hpp"
#include "fmt/os.h"
SMD::SMD(const std::string &name, const SystemInfo &systemInfo, const std::string &rst7, const std::string &refc, bool irest, float temp, const std::string &restraintmask, float restraint_wt, int nstlim, float cut, int ntc, int ntf, float tautp, float taup, int mcbarint, float gamma_ln, float dt, int nscm, int ntwx, int ntpr, int ntwr)
{
}
void SMD::Run()
{
    Npt::writeInput();
    Npt::charmmWater();
    Npt::Thermostat();
    if (ntb_ == 2)
    {
        Npt::barostat();
    }
    Npt::restraint();
    Npt::writeEnd();
    pull();
    Npt::runMd();
}
SMD *SMD::setCut(float cut)
{
    return dynamic_cast<SMD*>(Npt::setCut(cut));
}
SMD *SMD::setNTpr(int ntpr)
{
    return dynamic_cast<SMD*>(Npt::setNTpr(ntpr));
}
SMD *SMD::setNTwx(int ntwx)
{
    return dynamic_cast<SMD*>(Npt::setNTwx(ntwx));
}
SMD *SMD::setNTwr(int ntwr)
{
    return dynamic_cast<SMD*>(Npt::setNTwr(ntwr));
}
SMD *SMD::setNstLim(int nstlim)
{
    return dynamic_cast<SMD*>(Npt::setNstLim(nstlim));
}
SMD *SMD::setIrest(bool irest)
{
    return dynamic_cast<SMD*>(Npt::setIrest(irest));
}
SMD *SMD::setTautp(float tautp)
{
    return dynamic_cast<SMD*>(Npt::setTautp(tautp));
}
SMD *SMD::settaup(float taup)
{
    return dynamic_cast<SMD*>(Npt::settaup(taup));
}
SMD *SMD::setMcbarint(int mcbarint)
{
    return dynamic_cast<SMD*>(Npt::setMcbarint(mcbarint));
}
SMD *SMD::setGammaLn(float gamma_ln)
{
    return dynamic_cast<SMD*>(Npt::setGammaLn(gamma_ln));
}
SMD *SMD::setDt(float dt)
{
    return dynamic_cast<SMD*>(Npt::setDt(dt));
}
SMD *SMD::setNscm(int nscm)
{
    return dynamic_cast<SMD*>(Npt::setNscm(nscm));
}
SMD *SMD::setNtx(int ntx)
{
    return dynamic_cast<SMD*>(Npt::setNtx(ntx));
}
SMD *SMD::setNtc(int ntc)
{
    return dynamic_cast<SMD*>(Npt::setNtc(ntc));
}
SMD *SMD::setNtf(int ntf)
{
    return dynamic_cast<SMD*>(Npt::setNtf(ntf));
}
SMD *SMD::setTemp(float temp)
{
    return dynamic_cast<SMD*>(Npt::setTemp(temp));
}
SMD *SMD::setBarostat(const std::string & barostat)
{
    return dynamic_cast<SMD*>(Npt::setBarostat(barostat));
}
SMD *SMD::setThermostat(const std::string & thermostat)
{
    return dynamic_cast<SMD*>(Npt::setThermostat(thermostat));
}
SMD *SMD::setRestraintMask(std::string restraintmask)
{
    return dynamic_cast<SMD*>(Npt::setRestraintMask(restraintmask));
}
SMD *SMD::setRestraint_wt(float restraint_wt)
{
    return dynamic_cast<SMD*>(Npt::setRestraint_wt(restraint_wt));
}
void SMD::pull()
{
    fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
    out.print("&end\n");
}
