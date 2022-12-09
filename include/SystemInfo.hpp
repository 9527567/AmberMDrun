//
// Created by jack on 2022/9/19.
//

#ifndef AMBERMD_SYSTEMINFO_HPP
#define AMBERMD_SYSTEMINFO_HPP

#include "fmt/format.h"
#include "noncopyable.hpp"
#include <optional>
#include <string>
#include <vector>
#include <unordered_set>
class ResName
{
public:
    static inline const std::vector<std::string> Protein{
            "ACE",
            "ALA",
            "ARG",
            "ASH",
            "AS4",
            "ASN",
            "ASP",
            "CALA",
            "CARG",
            "CASN",
            "CASP",
            "CCYS",
            "CCYX",
            "CGLN",
            "CGLU",
            "CGLY",
            "CHID",
            "CHIE",
            "CHIP",
            "CHIS",
            "CHYP",
            "CILE",
            "CLEU",
            "CLYS",
            "CMET",
            "CPHE",
            "CPRO",
            "CSER",
            "CTHR",
            "CTRP",
            "CTYR",
            "CVAL",
            "CYM",
            "CYS",
            "CYX",
            "GLH",
            "GL4",
            "GLN",
            "GLU",
            "GLY",
            "HID",
            "HIE",
            "HIP",
            "HIS",
            "HYP",
            "ILE",
            "LEU",
            "LYN",
            "LYS",
            "MET",
            "NALA",
            "NARG",
            "NASN",
            "NASP",
            "NCYS",
            "NCYX",
            "NGLN",
            "NGLU",
            "NGLY",
            "NHE",
            "NHID",
            "NHIE",
            "NHIP",
            "NHIS",
            "NILE",
            "NLEU",
            "NLYS",
            "NME",
            "NMET",
            "NPHE",
            "NPRO",
            "NSER",
            "NTHR",
            "NTRP",
            "NTYR",
            "NVAL",
            "PHE",
            "PRO",
            "SER",
            "THR",
            "TRP",
            "TYR",
            "VAL"};
    static inline const std::vector<std::string> DNA{
            "DA",
            "DA3",
            "DA5",
            "DAN",
            "DC",
            "DC3",
            "DC5",
            "DCN",
            "DG",
            "DG3",
            "DG5",
            "DGN",
            "DT",
            "DT3",
            "DT5",
            "DTN"};
    static inline const std::vector<std::string> RNA{
            "A",
            "A3",
            "A5",
            "AMP",
            "AN",
            "C",
            "C3",
            "C5",
            "CMP",
            "CN",
            "G",
            "G3",
            "G5",
            "GMP",
            "GN",
            "OHE",
            "U",
            "U3",
            "U5",
            "UMP",
            "UN"};
    static inline const std::vector<std::string> Lipid{
            "POPE",
            "DOPC",
            "AR",
            "CHL",
            "DHA",
            "LAL",
            "MY",
            "OL",
            "PA",
            "PC",
            "PE",
            "PGR",
            "PH-",
            "PS",
            "ST"};
    static inline const std::vector<std::string> Carbo{
            "0GB",
            "4GB",
            "0YA",
            "4YA",
            "0fA",
            "0YB",
            "2MA",
            "4YB",
            "NLN",
            "UYB",
            "VMB",
            "0SA",
            "6LB",
            "ROH"};
    static inline const std::vector<std::string> CharmmWater{
            "TIP3"};
    static inline const std::vector<std::string> Water{
            "WAT",
            "SOL"};
};


class SystemInfo
{
public:
    SystemInfo() = default;
    explicit SystemInfo(const std::string &parm7File, const std::string &rst7File, const std::string &runMin = "pmemd.cuda_DPFP", const std::string &runMd = "pmemd.cuda");
    [[nodiscard]] int getNprotein() const
    {
        return nProtein_;
    }
    [[nodiscard]] int getnDna() const
    {
        return nDna_;
    }
    [[nodiscard]] int getnRna() const
    {
        return nRna_;
    }
    [[nodiscard]] int getnLipid() const
    {
        return nLipid_;
    }
    [[nodiscard]] int getnUnKnown_() const
    {
        return nunKnown_;
    }
    [[nodiscard]] int getnCharmmWater_() const
    {
        return nCharmmWater_;
    }
    [[nodiscard]] int getnWater() const
    {
        return nWater_;
    }
    [[nodiscard]] int getnCarbo() const
    {
        return nCarbo_;
    }
    [[nodiscard]] bool getHasCharmmWater() const
    {
        return hasCharmmWater_;
    }
    [[nodiscard]] bool getHasOrthoBox() const
    {
        return hasOrthoBox_;
    }
    [[nodiscard]] std::string getRunMin() const
    {
        return runMin_;
    }
    [[nodiscard]] std::string getRunMd() const
    {
        return runMd_;
    }
    [[nodiscard]] std::string getParm7File() const
    {
        return parm7File_;
    };
    [[nodiscard]] std::string getRst7File() const
    {
        return rst7File_;
    };
    [[nodiscard]] std::optional<std::string> getHeavyMask() const
    {
        int &&num = nProtein_ + nDna_ + nRna_ + nLipid_ + nCarbo_;
        if (num > 0)
        {
            return fmt::format("\":1-{}&!@H=\"", num);
        } else
        {
            return std::nullopt;
        }
    }
    [[nodiscard]] std::optional<std::string> getBackBoneMask() const;

private:
    std::string runMin_;
    std::string runMd_;
    std::string runCpptraj_;
    std::string parm7File_;
    std::string rst7File_;
    int nProtein_ = 0;
    int nDna_ = 0;
    int nRna_ = 0;
    int nLipid_ = 0;
    int nunKnown_ = 0;
    int nCharmmWater_ = 0;
    int nWater_ = 0;
    int nCarbo_ = 0;
    bool hasCharmmWater_ = false;
    bool hasOrthoBox_;
    std::pair<int, int> Protein_{-1,-1};
    std::pair<int, int> DNA_{-1,-1};
    std::pair<int, int> RNA_{-1,-1};
    std::pair<int, int> Lipid_{-1,-1};
    std::pair<int, int> Carbo_{-1,-1};
    std::pair<int, int> CharmmWater_{-1,-1};
    std::pair<int, int> Water_{-1,-1};
    std::unordered_set<std::string> unKnownRes_;
};

#endif//AMBERMD_SYSTEMINFO_HPP
