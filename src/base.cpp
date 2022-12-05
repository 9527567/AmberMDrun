//
// Created by jack on 2022/9/19.
//
#include "base.hpp"

#include "fmt/core.h"
#include "fmt/os.h"
#include <utility>
Base::Base(const std::string &name, SystemInfo systemInfo, const std::string &rst7,const std::string &refc, bool irest, const std::string &restranintmask, float restraint_wt, float cut)
{
    name_ = name;
    systemInfo_ = systemInfo;
    rst7_ = rst7;
    iRest_ = irest;
    restraintMask_ = restranintmask;
    restraint_wt_ = restraint_wt;
    cut_ = cut;
}
void Base::writeInput()
{
    fmt::ostream out = fmt::output_file(name_ + ".in");
    out.print("Minimization:{}\n", name_);
    out.print("&cntrl\n");
}
void Base::Run()
{
    writeInput();
    charmmWater();
    restraint();
    writeEnd();
    runMd();
}
void Base::charmmWater()
{
    if (systemInfo_.getHasCharmmWater())
    {
        hasCharmmWater_ = true;
    }
    if (hasCharmmWater_)
    {
        fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
        out.print("   WATNAM = 'TIP3', OWTNM = 'OH2',");
    }
}
void Base::writeEnd()
{
    fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
    out.print("&end\n");
}
void Base::restraint()
{
    setRestraintMask(restraintMask_);
    fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
    if (restraintMask_.empty())
    {
        out.print("ntr=0");
        out.print("\n");
    } else
    {
        out.print("ntr=1,");
        out.print("restraintmask={},", restraintMask_);
        out.print("restraint_wt={},", restraint_wt_);
        out.print("\n");
    }
}
// 最简单的版本
void Base::setRestraintMask(std::string appendMask)
{
    if (restraintMask_.empty())
    {
        restraintMask_ = fmt::format("\":1-{}&!@H=\"", systemInfo_.getNprotein() + systemInfo_.getnDna() + systemInfo_.getnRna() + systemInfo_.getnLipid() + systemInfo_.getnCarbo());

    } else
    {
        restraintMask_ = fmt::format("\":1-{}&!@H=|:{}\"", systemInfo_.getNprotein() + systemInfo_.getnDna() + systemInfo_.getnRna() + systemInfo_.getnLipid() + systemInfo_.getnCarbo(), appendMask);
    }
}
[[maybe_unused]] Base *Base::setCut(float cut)
{
    cut_ = cut;
    return this;
}
void Base::appendMask(std::string mask)
{
}
Base *Base::setNTwx(int ntwx)
{
    nTwx_ = ntwx;
    return this;
}
Base *Base::setNTwr(int ntwr)
{
    nTwr_ = ntwr;
    return this;
}
Base *Base::setNTpr(int ntpr)
{
    nTpr_ = ntpr;
    return this;
}
void Base::runMd()
{
    std::string run = "sander";
    if (iMin_ == 1)
    {
        run = systemInfo_.getRunMin();
    } else
    {
        run = systemInfo_.getRunMd();
    }
    std::string execCommamd = fmt::format("{} -O -i {}.in -p {} -c {} -ref {} -o {}.out -r {}.rst7 -x {}.nc -inf {}.mdinfo", run, name_, systemInfo_.getParm7File(), rst7_, refc_, name_, name_, name_, name_);
    std::vector<std::string> result = executeCMD(execCommamd);
    for (auto i: result)
    {
        fmt::print("{}", i);
    }
}
