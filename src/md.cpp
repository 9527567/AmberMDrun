//
// Created by jack on 2022/9/21.
//
#include "md.hpp"
#include "fmt/os.h"
Md::Md(const std::string &name, SystemInfo systemInfo, std::string restrintmask, float restrant_wt, int nstlim,float cut, bool irest, int ntb, int ntc, int ntf, float tautp, float taup, int mcbarint, int gamma_ln, float dt, int nscm, int ntwx, int ntpr, int ntwr) : Base(name, systemInfo, restrintmask, restrant_wt,cut)
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
    ntwx_ = ntwx;
    ntpr_ = ntpr;
    ntwr_ = ntwr;
    ntb_ = ntb;
    ntc_ = ntc;
    ntf_ = ntf;
    cut_ = cut;
}
void Md::operator()(std::string name, int nstlim, bool irest, int ntb, int ntc, int ntf, float tautp, float taup, int mcbarint, int gamma_ln, float dt, int nscm, int ntwx, int ntpr, int ntwr)
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
    ntwx_ = ntwx;
    ntpr_ = ntpr;
    ntwr_ = ntwr;
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
    out.print("ntwx={},", ntwx_);
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
}
void Md::Thermostat()
{
}
