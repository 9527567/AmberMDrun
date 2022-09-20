#include "SystemInfo.hpp"
#include "cmdLine.hpp"
#include <iostream>
#include <string>
auto flag(int &argc, char *argv[]) -> cmdline::parser
{
    cmdline::parser flags;
    flags.add<std::string>("parm7", 'p', "amber top file", true, "");
    flags.add<std::string>("rst7", 'c', "amber rst file", true, "");
    flags.add<std::string>("temp", 't', "Temperature", true, "");
    flags.add<std::string>("thermo", 0, "Thermostat", false, "langevin",
                           cmdline::oneof<std::string>("berendsen", "langevin"));
    flags.add<std::string>("baro", 0, "Barostat", false, "montecarlo",
                           cmdline::oneof<std::string>("berendsen", "montecarlo"));
    flags.add<std::string>("finalthermo", 0, "Final stage thermostat", false, "langevin",
                           cmdline::oneof<std::string>("berendsen", "langevin"));
    flags.add<std::string>("finalbaro", 0, "Final stage barostat", false, "montecarlo",
                           cmdline::oneof<std::string>("berendsen", "montecarlo"));
    flags.add<std::string>("mask", 0, "Additional mask to use for restraints during steps 1-8.", false, "");
    flags.add<std::string>("pmask", 0, "Restraint mask to use during production (steps 9 and above).", false, "");
    flags.add<std::string>("pref", 0, "Optional reference structure to use for '--pmask'.", false, "");
    flags.add<std::string>("charmmwater", 0, "If specified assume CHARMM water (i.e. 'TIP3').", false, "");
    flags.add<std::string>("cutoff", 0, "If specified, override default cutoffs with <cut>.", false, "");
    flags.add<std::string>("norestart", 0, "Do standard Eq with no restarts.", false, "");
    flags.add<std::string>("skipfinaleq", 0, "If specified, skip final eq. (step 10).", false, "");
    flags.add("overwrite", 'O', "Overwrite existing files, otherwise skip.", false, false);
    flags.parse_check(argc, argv);
    return flags;
}

int main(int argc, char *argv[])
{
    auto f = flag(argc, argv);
    SystemInfo systemInfo = SystemInfo(f.get<std::string>("parm7"));
    printf("%d\n",systemInfo.getNprotein());
}