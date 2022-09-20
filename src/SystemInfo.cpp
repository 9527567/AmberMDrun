//
// Created by jack on 2022/9/19.
//
#include "SystemInfo.hpp"
#include "common.hpp"
#include <string>

SystemInfo::SystemInfo(const std::string &filename)
{
    auto result = executeCMD("cpptraj -p " + filename + " --resmask \\*");
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
    try
    {
        if (nWater_ > 0 && hasCharmmWater_)
        {
            throw "Error: Charmm water and regular water present.";
        }
    }
    catch (const std::string &message)
    {
        printf("%s\n", message.c_str());
    }
}
