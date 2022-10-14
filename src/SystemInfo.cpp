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
SystemInfo::SystemInfo(const std::string &filename, const std::string &runMin, const std::string &runMd)
{
    char *amberHome = getenv("AMBERHOME");
    std::function<void()> getRunExec = [&]() {
        if (amberHome == nullptr)
        {
            throw std::runtime_error("at least AamberTools need!");
        } else
        {
            long cpu_nums;
            cpu_nums = sysconf(_SC_NPROCESSORS_ONLN) / 2;
            auto temp = std::string(amberHome);
            if (std::filesystem::exists(temp + "/" + "bin/" + runMin))
                runMin_ = temp + "/" + "bin/" + runMin;
            if (std::filesystem::exists(temp + "/" + "bin/" + runMd))
                runMd_ = temp + "/" + "bin/" + runMd;
            else if (std::filesystem::exists(temp + "/" + "bin/" + "pmemd.MPI"))
            {
                runMin_ = "mpirun -np " + std::to_string(cpu_nums) + " " + temp + "/" + "bin/" + "pmemd.MPI";
                runMd_ = "mpirun -np " + std::to_string(cpu_nums) + " " + temp + "/" + "bin/" + "pmemd.MPI";
            } else if (std::filesystem::exists(temp + "/" + "bin/" + "sander.MPI"))
            {
                runMin_ = "mpirun -np " + std::to_string(cpu_nums) + " " + temp + "/" + "bin/" + "sander.MPI";
                runMd_ = "mpirun -np " + std::to_string(cpu_nums) + " " + temp + "/" + "bin/" + "sander.MPI";
            } else if (std::filesystem::exists(temp + "/" + "bin/" + "pmemd"))
            {
                runMin_ = temp + "/" + "bin/" + "pmemd";
                runMd_ = temp + "/" + "bin/" + "pmemd";
            } else if (std::filesystem::exists(temp + "/" + "bin/" + "sander"))
            {
                runMin_ = temp + "/" + "bin/" + "sander";
                runMd_ = temp + "/" + "bin/" + "sander";
            } else
            {
                throw std::runtime_error("需要动力学引擎，检查amber安装情况");
            }
            if (std::filesystem::exists(temp + "/" + "bin/" + "cpptraj"))
            {
                runCpptraj_ = temp + "/" + "bin/" + "cpptraj";
            }
        }
    };
    getRunExec();
    std::vector<std::string> result = executeCMD(this->runCpptraj_ + " -p " + filename + " --resmask \\*");
    for (int i = 1; i < result.size(); ++i)
    {
        std::string resname = result[i].substr(6, 4);
        trim(resname);
        if (isIn(resname, ResName::Protein))
        {
            nProtein_++;
        } else if (isIn(resname, ResName::DNA))
        {
            nDna_++;
        } else if (isIn(resname, ResName::RNA))
        {
            nRna_++;
        } else if (isIn(resname, ResName::Lipid))
        {
            nLipid_++;
        } else if (isIn(resname, ResName::Carbo))
        {
            nCarbo_++;
        } else if (isIn(resname, ResName::CharmmWater))
        {
            nCharmmWater_++;
        } else if (isIn(resname, ResName::Water))
        {
            nWater_++;
        } else
        {
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
    result = executeCMD("echo \"list parm\" | cpptraj -p " + filename + "| grep box");
    if (result[0].find("Orthorhombic") == std::string::npos)
    {
        hasOrthoBox_ = false;
    } else
    {
        hasOrthoBox_ = true;
    }
}
