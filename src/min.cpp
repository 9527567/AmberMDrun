//
// Created by jack on 2022/9/21.
//
#include "min.hpp"
#include "fmt/core.h"
#include "fmt/os.h"
Min::Min(std::string name,int nTmin, int maxCyc, int nCyc, int nTwx, int nTpr, int nTwr)
{
    name_ = name;
    nTmin_ = nTmin;
    maxCyc_=maxCyc;
    nCyc_ = nCyc;
    nTwx_=nTwx;
    nTpr_ = nTwr;
    iMin_ = 1;
}
void Min::operator()(std::string name, int nTmin, int maxCyc, int nCyc, int nTwx, int nTpr, int nTwr)
{
    name_ = name;
    nTmin_ = nTmin;
    maxCyc_=maxCyc;
    nCyc_ = nCyc;
    nTwx_=nTwx;
    nTpr_ = nTwr;
    iMin_ = 1;
}
void Min::writeInput()
{
    Base::writeInput();
    fmt::ostream out = fmt::output_file(name_+".in",fmt::file::WRONLY|fmt::file::APPEND);
    out.print("imin={},",iMin_);
    out.print("ntmin={},",nTmin_);
    out.print("maxcyc={},",maxCyc_);
    out.print("ncyc={},",nCyc_);
    out.print("\n");
    out.print("ntwx={},",nTwx_);
    out.print("ioutfm={},",iOutfm_);
    out.print("ntxo={},",nTxo_);
    out.print("ntpr={},",nTpr_);
    out.print("ntwr={},",nTwr_);
    out.print("\n");
    out.print("ntc={},",ntc_);
    out.print("ntf={},",ntf_);
    out.print("ntb={},",ntb_);
}
