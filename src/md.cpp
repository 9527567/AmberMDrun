//
// Created by jack on 2022/9/21.
//
#include "md.hpp"
#include "fmt/os.h"
Md::Md(const std::string &name, SystemInfo systemInfo, std::string restrintmask, float restrant_wt, int nstlim, float cut, bool irest, int ntb, int ntc, int ntf, float tautp, float taup, int mcbarint, float gamma_ln, float dt, int nscm, int ntwx, int ntpr, int ntwr) : Base(name, systemInfo, restrintmask, restrant_wt, cut)
{
    name_ = name;
    nstLim_ = nstlim;
    iRest_ = irest;
    tautp_ = tautp;
    taup_ = taup;
    mcbarint_ = mcbarint;
    gamma_ln_ = gamma_ln;
    dt_ = dt;
    nscm_ = nscm;
    nTwx_ = ntwx;
    nTpr_ = ntpr;
    nTwr_ = ntwr;
    ntb_ = ntb;
    ntc_ = ntc;
    ntf_ = ntf;
    cut_ = cut;
    ntpFlags_ = 1;
    if (systemInfo_.getnLipid() != 0)
    {
        ntpFlags_ = 2;
    }
}
void Md::operator()(std::string name, int nstlim, bool irest, int ntb, int ntc, int ntf, float tautp, float taup, int mcbarint, float gamma_ln, float dt, int nscm, int ntwx, int ntpr, int ntwr)
{
    name_ = name;
    nstLim_ = nstlim;
    iRest_ = irest;
    ntb_ = ntb;
    tautp_ = tautp;
    taup_ = taup;
    mcbarint_ = mcbarint;
    gamma_ln_ = gamma_ln;
    dt_ = dt;
    nscm_ = nscm;
    nTwx_ = ntwx;
    nTpr_ = ntpr;
    nTwr_ = ntwr;
    ntb_ = ntb;
    ntc_ = ntc;
    ntf_ = ntf;
}
void Md::Run()
{
    Base::Run();
}
void Md::writeInput()
{
    Base::writeInput();
    fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
    out.print("imin={},", iMin_);
    out.print("nstlim={},", nstLim_);
    out.print("dt={},", dt_);
    out.print("\n");
    out.print("ntx={},", ntx_);
    out.print("irest={},", iRest_);
    out.print("ig=-1,");
    out.print("\n");
    out.print("ntwx={},", nTpr_);
    out.print("ntwv={},", -1);
    out.print("ioutfm={},", iOutfm_);
    out.print("ntxo={},", nTxo_);
    out.print("ntpr={},", nTpr_);
    out.print("ntwr={},", nTwr_);
    out.print("\n");
    out.print("iwrap={},", 0);
    out.print("nscm={},", nscm_);
    out.print("\n");
    out.print("ntc={},", ntc_);
    out.print("ntf={},", ntf_);
    out.print("ntb={},", ntb_);
    out.print("\n");
}
void Md::charmmWater()
{
    Base::charmmWater();
}
void Md::restraint()
{
    Base::restraint();
}
void Md::writeEnd()
{
    Base::writeEnd();
}
void Md::setRestraintMask(std::string appendMask)
{
    Base::setRestraintMask(appendMask);
}
void Md::barostat()
{
    if (baroType_ == baro::berendsen)
    {
        fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
        out.print("ntp={},", ntpFlags_);
        out.print("taup={}", taup_);
        out.print("pres0={}", 1.0);
        out.print("\n");
    } else if (baroType_ == baro::montecarlo)
    {
        fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
        out.print("ntp={},", ntpFlags_);
        out.print("barostat={}", 2);
        out.print("pres0={}", 1.0);
        out.print("mcbarint={},", mcbarint_);
        out.print("\n");
    } else
    {
        throw fmt::format_error("The thermo must be berendsen of montecarlo");
    }
}
void Md::Thermostat()
{
    if (thermoType_ == thermo::berendsen)
    {
        fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
        out.print("ntt={},", 1);
        out.print("tautp={}", tautp_);
        out.print("temp0={}", 300);
        out.print("tempi={},", 300);
        out.print("\n");
    } else if (thermoType_ == thermo::langevin)
    {
        fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
        out.print("ntt={},", 3);
        out.print("gamma_ln={}", gamma_ln_);
        out.print("temp0={}", 300);
        out.print("tempi={},", 300);
        out.print("\n");
    } else
    {
        throw fmt::format_error("The thermo must be berendsen of langevin");
    }
}
Md *Md::setCut(float cut)
{
    cut_ = cut;
    return this;
}
Md *Md::setNTpr(int ntpr)
{
    nTpr_ = ntpr;
    return this;
}
Md *Md::setNTwx(int ntwx)
{
    nTwx_ = ntwx;
    return this;
}
Md *Md::setNTwr(int ntwr)
{
    nTwr_ = ntwr;
    return this;
}
Md *Md::setNstLim(int nstlim)
{
    nstLim_ = nstlim;
    return this;
}
Md *Md::setIrest(bool irest)
{
    if (irest)
    {
        iRest_ = irest;
    } else
    {
        iRest_ = irest;
    }
    return this;
}
Md *Md::setTautp(float tautp)
{
    tautp_ = tautp;
    return this;
}
Md *Md::settaup(float taup)
{
    taup_ = taup;
    return this;
}
Md *Md::setMcbarint(int mcbarint)
{
    mcbarint_ = mcbarint;
    return this;
}
Md *Md::setGammaLn(float gamma_ln)
{
    gamma_ln_ = gamma_ln;
    return this;
}
Md *Md::setDt(float dt)
{
    dt_ = dt;
    return this;
}
Md *Md::setNscm(int nscm)
{
    nscm_ = nscm;
    return this;
}
Md *Md::setNtx(int ntx)
{
    ntx_ = ntx;
    return this;
}
Md *Md::setNtc(int ntc)
{
    ntc_ = ntc;
    return this;
}
Md *Md::setNtf(int ntf)
{
    ntf_ = ntf;
    return this;
}
Md *Md::setNtb(int ntb)
{
    ntb_ = ntb;
    return this;
}
Md *Md::setBarostat(std::string baroType)
{
    return this;
}
Md *Md::setThermostat(std::string thermoType)
{
    return this;
}
