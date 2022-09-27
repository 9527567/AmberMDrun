//
// Created by jack on 2022/9/19.
//

#ifndef AMBERMD_SYSTEMINFO_HPP
#define AMBERMD_SYSTEMINFO_HPP

#include "noncopyable.hpp"
#include <string>
#include <vector>
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
            "WAT"};
};


class SystemInfo
{
public:
    SystemInfo() = default;
    explicit SystemInfo(const std::string &filename);
    int getNprotein() const
    {
        return nProtein_;
    }
    int getnDna() const
    {
        return nDna_;
    }
    int getnRna() const
    {
        return nRna_;
    }
    int getnLipid() const
    {
        return nLipid_;
    }
    int getnUnKnown_() const
    {
        return nunKnown_;
    }
    int getnCharmmWater_() const
    {
        return nCharmmWater_;
    }
    int getnWater() const
    {
        return nWater_;
    }
    int getnCarbo() const
    {
        return nCarbo_;
    }
    bool getHasCharmmWater() const
    {
        return hasCharmmWater_;
    }

private:
    int nProtein_ = 0;
    int nDna_ = 0;
    int nRna_ = 0;
    int nLipid_ = 0;
    int nunKnown_ = 0;
    int nCharmmWater_ = 0;
    int nWater_ = 0;
    int nCarbo_ = 0;
    bool hasCharmmWater_ = false;
};

#endif//AMBERMD_SYSTEMINFO_HPP
