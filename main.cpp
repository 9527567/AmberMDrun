#include "SystemInfo.hpp"
#include "base.hpp"
#include "cmdLine.hpp"
#include "fmt/core.h"
#include "md.hpp"
#include "min.hpp"
#include "nvt.hpp"
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
    //    flags.add<std::string>("thermo", 0, "Thermostat", false, "langevin",
    //                           cmdline::oneof<std::string>("berendsen", "langevin"));
    //    flags.add<std::string>("baro", 0, "Barostat", false, "montecarlo",
    //                           cmdline::oneof<std::string>("berendsen", "montecarlo"));
    //    flags.add<std::string>("finalthermo", 0, "Final stage thermostat", false, "langevin",
    //                           cmdline::oneof<std::string>("berendsen", "langevin"));
    //    flags.add<std::string>("finalbaro", 0, "Final stage barostat", false, "montecarlo",
    //                           cmdline::oneof<std::string>("berendsen", "montecarlo"));
    //    flags.add<std::string>("mask", 0, "Additional mask to use for restraints during steps 1-8.", false, "");
    //    flags.add<std::string>("pmask", 0, "Restraint mask to use during production (steps 9 and above).", false, "");
    //    flags.add<std::string>("pref", 0, "Optional reference structure to use for '--pmask'.", false, "");
    //    flags.add<std::string>("charmmwater", 0, "If specified assume CHARMM water (i.e. 'TIP3').", false, "");
    //    flags.add<std::string>("cutoff", 0, "If specified, override default cutoffs with <cut>.", false, "");
    //    flags.add<std::string>("norestart", 0, "Do standard Eq with no restarts.", false, "");
    //    flags.add("skipfinaleq", 0, "If specified, skip final eq. (step 10).", false, false);
    //    flags.add("overwrite", 'O', "Overwrite existing files, otherwise skip.", false, false);
    flags.parse_check(argc, argv);
    return flags;
}

int prep(const std::string &rst7, SystemInfo s, float temp, const std::string &heavymask, const std::string &backbonemask, int ns)
{
    auto min1 = Min("step1", s, rst7, rst7);
    min1.setRestraint_wt(5.0);
    min1.setRestraintMask(heavymask);
    min1.Run();
    auto nvt1 = Nvt("setp2", s, "step2.rst7", "step2.rst7");
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