//
// Created by jack on 2022/9/21.
//
#include "min.hpp"
#include "fmt/core.h"
#include "fmt/os.h"
Min::Min(std::string name, SystemInfo systemInfo, std::string restrintmask, float restrant_wt, float cut, int nTmin, int maxCyc, int nCyc, int nTwx, int nTpr, int nTwr) : Base(name, systemInfo, restrintmask, restrant_wt, cut)
{
    name_ = name;
    nTmin_ = nTmin;
    maxCyc_ = maxCyc;
    nCyc_ = nCyc;
    nTwx_ = nTwx;
    nTpr_ = nTwr;
    nTwr_ = nTwr;
    iMin_ = 1;
}
void Min::operator()(std::string name, int nTmin, int maxCyc, int nCyc, int nTwx, int nTpr, int nTwr)
{
    name_ = name;
    nTmin_ = nTmin;
    maxCyc_ = maxCyc;
    nCyc_ = nCyc;
    nTwx_ = nTwx;
    nTpr_ = nTwr;
    iMin_ = 1;
}
void Min::writeInput()
{
    Base::writeInput();
    fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
    out.print("imin={},", iMin_);
    out.print("ntmin={},", nTmin_);
    out.print("maxcyc={},", maxCyc_);
    out.print("ncyc={},", nCyc_);
    out.print("\n");
    out.print("ntwx={},", nTwx_);
    out.print("ioutfm={},", iOutfm_);
    out.print("ntxo={},", nTxo_);
    out.print("ntpr={},", nTpr_);
    out.print("ntwr={},", nTwr_);
    out.print("\n");
    out.print("ntc={},", ntc_);
    out.print("ntf={},", ntf_);
    out.print("ntb={},", ntb_);
    out.print("cut={:.1f},", cut_);
    out.print("\n");
}
void Min::charmmWater()
{
    Base::charmmWater();
}
void Min::restraint()
{
    Base::restraint();
}
void Min::writeEnd()
{
    Base::writeEnd();
}
void Min::Run()
{
    Base::Run();
}
void Min::setRestraintMask(std::string appendMask)
{
    Base::setRestraintMask(appendMask);
}
Min *Min::setCut(float cut)
{
    cut_ = cut;
    return this;
}
Min *Min::setMaxCyc(int maxcyc)
{
    maxCyc_ = maxcyc;
    return this;
}
Min *Min::setNCyc(int cyc)
{
    nCyc_ = cyc;
    return this;
}
Min *Min::setNTim(int ntmin)
{
    nTmin_ = ntmin;
    return this;
}
Min *Min::setNTpr(int ntpr)
{
    nTpr_ = ntpr;
    return this;
}
Min *Min::setNTwr(int ntwr)
{
    nTwr_ = ntwr;
    return this;
}
Min *Min::setNTwx(int ntwx)
{
    nTwx_ = ntwx;
    return this;
}
