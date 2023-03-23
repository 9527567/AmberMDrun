#include "SystemInfo.hpp"
#include "cmdLine.hpp"
#include "fmt/core.h"
#include "min.hpp"
#include "npt.hpp"
#include "nvt.hpp"
#include "tqdm.hpp"
#include <memory>
#include <string>
auto flag(int &argc, char *argv[]) -> cmdline::parser
{
    cmdline::parser flags;
    flags.add<std::string>("parm7", 'p', "amber top file", true, "");
    flags.add<std::string>("rst7", 'c', "amber rst file", true, "");
    flags.add<float>("temp", 't', "Temperature", false, 303.15);
    flags.add<int>("ns", 'n', "time for MD(ns)", false, 100);
    flags.add<std::string>("addmask", 0, "add restarint mask", false, "");

    flags.parse_check(argc, argv);
    return flags;
}

void prep(const std::string &rst7, SystemInfo s, float temp, const std::string &heavymask, const std::string &backbonemask, int ns)
{
    auto min1 = std::make_unique<Min>("step1", s, rst7, rst7);
    min1->setRestraint_wt(5.0)->setRestraintMask(heavymask)->Run();
    auto nvt1 = std::make_unique<Nvt>("step2", s, "step1.rst7", "step1.rst7");
    nvt1->setRestraintMask(heavymask)->setRestraint_wt(5.0)->setNstLim(15000)->setTautp(0.5)->Run();
    auto min2 = std::make_unique<Min>("step3", s, "step2.rst7", "step2.rst7");
    min2->setRestraint_wt(2.0)->setRestraintMask(heavymask)->Run();
    auto min3 = std::make_unique<Min>("step4", s, "step3.rst7", "step3.rst7");
    min3->setRestraintMask(backbonemask)->setRestraint_wt(0.1)->Run();
    auto min4 = std::make_unique<Min>("step5", s, "step4.rst7", "step4.rst7");
    min4->Run();
    auto npt1 = std::make_unique<Npt>("step6", s, "step5.rst7", "step5.rst7");
    npt1->setTemp(temp)->setRestraintMask(heavymask)->setRestraint_wt(1.0);
    npt1->Run();
    auto npt2 = std::make_unique<Npt>("step7", s, "step6.rst7", "step5.rst7");
    npt2->setTemp(temp)->setRestraintMask(heavymask)->setRestraint_wt(0.5)->Run();
    auto npt3 = std::make_unique<Npt>("step8", s, "step7.rst7", "step5.rst7");
    npt3->setTemp(temp)->setRestraintMask(backbonemask)->setRestraint_wt(0.5)->setIrest(true)->setNstLim(10000)->Run();
    auto npt4 = std::make_unique<Npt>("step9", s, "step8.rst7", "step5.rst7");
    npt4->setTemp(temp)->setIrest(true)->setDt(0.002)->setNscm(1000)->Run();
    auto md = std::make_unique<Npt>("Md", s, "step9.rst7", "step5.rst7");
    md->setTemp(temp)->setIrest(true)->setDt(0.002)->setNscm(1000)->setNTwx(50000)->setNstLim(ns * 500000);
    md->Run();
}


int main(int argc, char *argv[])
{
    auto f = flag(argc, argv);
    std::string parm7 = f.get<std::string>("parm7");
    std::string rst7 = f.get<std::string>("rst7");
    float temp = f.get<float>("temp");
    int time = f.get<int>("ns");
    std::string addmask = f.get<std::string>("addmask");
    auto s = SystemInfo(parm7, rst7);
    auto backbone = s.getBackBoneMask();
    auto heavy = s.getHeavyMask();
    std::string backbonemask{};
    std::string heavymask{};
    if (!addmask.empty())
    {
        if (s.getBackBoneMask().empty())
        {
            backbonemask = "\"" + addmask + "\"";
        } else
        {
            backbonemask = "\"" + s.getBackBoneMask() + "|" + addmask + "\"";
        }
        if (s.getHeavyMask().empty())
        {
            heavymask = "\"" + addmask + "\"";
        } else
        {
            heavymask = "\"" + s.getHeavyMask() + "|" + addmask + "\"";
        }
    }
    prep(rst7, s, temp, heavymask, backbonemask, 100);

    // MIN 01
}