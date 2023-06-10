//
// Created by jack on 2022/9/19.
//
#include "SystemInfo.hpp"
#include "common.hpp"
#include "fmt/core.h"
#include <filesystem>
#include <functional>
#include <string>
#include <unistd.h>
SystemInfo::SystemInfo(const std::string &parm7File, const std::string &rst7File, const std::string &runMin, const std::string &runMd)
{
    char *amberHome = getenv("AMBERHOME");
    std::function<void()> getRunExec = [&]() {
        if (amberHome == nullptr)
        {
            throw std::runtime_error("at least AmberTools need!");
        } else
        {
            long cpu_nums;
            cpu_nums = sysconf(_SC_NPROCESSORS_ONLN) / 2;
            auto runMinT {runMin};trim(runMinT);auto runMdT {runMd};trim(runMdT);
            if (runMinT == "pmemd.MPI"| runMinT == "sander.MPI")
            {
                runMin_ = "mpirun -np " + std::to_string(cpu_nums) + " " + runMinT;
            }
            else
            {
                runMin_ = runMinT;
            }
            if (runMdT == "pmemd.MPI"| runMdT == "sander.MPI")
            {
                runMd_ = "mpirun -np " + std::to_string(cpu_nums) + " " + runMdT;
            }
            else
            {
                runMd_ = runMdT;
            }

            runCpptraj_ = "cpptraj";
        }
    };
    getRunExec();
    parm7File_ = parm7File;
    rst7File_ = rst7File;
    std::vector<std::string> result = executeCMD(this->runCpptraj_ + " -p " + parm7File_ + " --resmask \\*");
    bool ProteinFlag = false;
    bool DNAFlag = false;
    bool RNAFlag = false;
    bool LipidFlag = false;
    bool CarboFlag = false;
    bool CharmmWaterFlag = false;
    bool WaterFlag = false;
    for (int i = 1; i < result.size(); ++i)
    {
        std::string resname = result[i].substr(6, 4);
        trim(resname);
        if (isIn(resname, ResName::Protein))
        {
            if (!ProteinFlag)
            {
                Protein_.first = i;
                ProteinFlag = true;
            } else
            {
                Protein_.second = i;
            }
            nProtein_++;
        } else if (isIn(resname, ResName::DNA))
        {
            if (!DNAFlag)
            {
                DNA_.first = i;
                DNAFlag = true;
            } else
            {
                DNA_.second = i;
            }
            nDna_++;
        } else if (isIn(resname, ResName::RNA))
        {
            if (!RNAFlag)
            {
                RNA_.first = i;
                RNAFlag = true;
            } else
            {
                RNA_.second = i;
            }
            nRna_++;
        } else if (isIn(resname, ResName::Lipid))
        {
            if (!LipidFlag)
            {
                Lipid_.first = i;
                LipidFlag = true;
            } else
            {
                Lipid_.second = i;
            }
            nLipid_++;
        } else if (isIn(resname, ResName::Carbo))
        {
            if (!CarboFlag)
            {
                Carbo_.first = i;
                CarboFlag = true;
            } else
            {
                Carbo_.second = i;
            }
            nCarbo_++;
        } else if (isIn(resname, ResName::CharmmWater))
        {
            if (!CharmmWaterFlag)
            {
                CharmmWater_.first = i;
                CharmmWaterFlag = true;
            } else
            {
                CharmmWater_.second = i;
            }
            nCharmmWater_++;
        } else if (isIn(resname, ResName::Water))
        {
            if (!WaterFlag)
            {
                Water_.first = i;
                WaterFlag = true;
            } else
            {
                Water_.second = i;
            }
            nWater_++;
        } else
        {
            unKnownRes_.emplace(resname);
            nunKnown_++;
        }
    }
    if (nCharmmWater_ > 0)
    {
        hasCharmmWater_ = true;
    }

    if (nWater_ > 0 && hasCharmmWater_)
    {
        throw std::runtime_error("Error: Charmm water and regular water present.");
    }

    result.clear();
    result = executeCMD("echo \"list parm\" | cpptraj -p " + parm7File_ + "| grep box");
    if (result[0].find("Orthorhombic") == std::string::npos)
    {
        hasOrthoBox_ = false;
    } else
    {
        hasOrthoBox_ = true;
    }
}
std::string SystemInfo::getBackBoneMask() const
{
    std::string result = {};
    int sum = 0;
    if (nProtein_ > 0)
    {
        result += fmt::format(":{}-{}@H,N,CA,HA,C,O",
                              Protein_.first, Protein_.second);
        sum += nProtein_;
    }
    if (nDna_ > 0)
    {
        if (sum == 0)
        {
            result += fmt::format(":{}-{}@P,O5',C5',C4',C3',O3",
                                  DNA_.first, DNA_.second);
        } else
        {
            result += fmt::format("|:{}-{}@P,O5',C5',C4',C3',O3",
                                  DNA_.first, DNA_.second);
        }
        sum += nDna_;
    }
    if (nRna_ > 0)
    {
        if (sum > 0)
        {
            result += fmt::format("|:{}-{}@P,O5',C5',C4',C3',O3",
                                  RNA_.first, RNA_.second);
        } else
        {
            result += fmt::format(":{}-{}@P,O5',C5',C4',C3',O3",
                                  RNA_.first, RNA_.second);
        }
        sum += nRna_;
    }
    if (nLipid_ > 0)
    {
        if (sum > 0)
        {
            result += fmt::format("|:{}-{}&!@H=",
                                  Lipid_.first, Lipid_.second);
        }else
        {
            result += fmt::format(":{}-{}&!@H=",
                                  Lipid_.first, Lipid_.second);
        }
        sum += nLipid_;
    }
    if (nCarbo_ > 0)
    {
        if (sum > 0)
        {
            result += fmt::format("|:{}-{}&!@H=",
                                  Carbo_.first, Carbo_.second);
        }else
        {
            result += fmt::format(":{}-{}&!@H=",
                                  Carbo_.first, Carbo_.second);
        }
    }
    return result;
}