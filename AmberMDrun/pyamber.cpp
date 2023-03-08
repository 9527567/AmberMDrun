//
// Created by jack on 2022/10/4.
//
#include "md.hpp"
#include "min.hpp"
#include "npt.hpp"
#include "nvt.hpp"
#include "gamd.hpp"
#include "pybind11/pybind11.h"
namespace py = pybind11;
PYBIND11_MODULE(_pyamber, m)
{
    py::class_<SystemInfo>(m, "SystemInfo")
            .def(py::init<const std::string &,
                          const std::string &,
                          const std::string &,
                          const std::string &>(),
                 py::arg("prmtop"),
                 py::arg("inpcrd"),
                 py::arg("runMin") = "pmemd.cuda_DPFP",
                 py::arg("runMd") = "pmemd.cuda")
            .def("getNprotein", &SystemInfo::getNprotein)
            .def("getnDna", &SystemInfo::getnDna)
            .def("getnRna", &SystemInfo::getnRna)
            .def("getnLipid", &SystemInfo::getnLipid)
            .def("getnUnKnown_", &SystemInfo::getnUnKnown_)
            .def("getnCharmmWater_", &SystemInfo::getnCharmmWater_)
            .def("getnWater", &SystemInfo::getnWater)
            .def("getnCarbo", &SystemInfo::getnCarbo)
            .def("getHasCharmmWater", &SystemInfo::getHasCharmmWater)
            .def("getHasOrthoBox", &SystemInfo::getHasOrthoBox)
            .def("getRunMin", &SystemInfo::getRunMd)
            .def("getRunMd", &SystemInfo::getRunMin)
            .def("getHeavyMask", &SystemInfo::getHeavyMask)
            .def("getBackBoneMask", &SystemInfo::getBackBoneMask);

    //    py::class_<Base>(m, "Base")
    //            .def(py::init<std::string,
    //                          SystemInfo, std::string,
    //                          float, float>(),
    //                 py::arg("name"),
    //                 py::arg("systeminfo"),
    //                 py::arg("restrintmask") = "",
    //                 py::arg("restrant_wt") = 0.0,
    //                 py::arg("cut") = 8.0)
    //            .def("setCut",&Base::setCut)
    //            .def("setNtwx",&Base::setNTwx)
    //            .def("setNtwr",&Base::setNTwr).
    //            def("setNtpr",&Base::setNTpr);
    py::class_<Min>(m, "Min", py::dynamic_attr())
            .def(py::init<const std::string &,
                          SystemInfo,
                          const std::string &,
                          const std::string &,
                          bool,
                          const std::string &,
                          float,
                          float,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int>(),
                 py::arg("name"),
                 py::arg("systemInfo"),
                 py::arg("ref"),
                 py::arg("refc"),
                 py::arg("irest") = false,
                 py::arg("restraintmask") = "",
                 py::arg("restraint_wt") = 0.0,
                 py::arg("cut") = 8.0,
                 py::arg("nTmin") = 2,
                 py::arg("maxCyc") = 1000,
                 py::arg("nCyc") = 10,
                 py::arg("nTwx") = 500,
                 py::arg("nTpr") = 50,
                 py::arg("nTwr") = 500)
            .def("setCut", &Min::setCut)
            .def("setNTpr", &Min::setNTpr)
            .def("setNTwr", &Min::setNTwr)
            .def("setNTwx", &Min::setNTwx)
            .def("setMaxCyc", &Min::setMaxCyc)
            .def("setNCyc", &Min::setNCyc)
            .def("setNTim", &Min::setNTim)
            .def("Run", &Min::Run)
            .def("setRestraintMask",&Min::setRestraintMask);
    py::class_<Md>(m, "Md", py::dynamic_attr())
            .def(py::init<const std::string &,
                          SystemInfo,
                          const std::string &,
                          const std::string &,
                          bool,
                          float,
                          const std::string &,
                          float,
                          int,
                          float,
                          int,
                          int,
                          int,
                          float,
                          float,
                          int,
                          float,
                          float,
                          int,
                          int,
                          int,
                          int>(),
                 py::arg("name"),
                 py::arg("systemInfo"),
                 py::arg("ref"),
                 py::arg("refc"),
                 py::arg("irest") = false,
                 py::arg("temp") = 303.15,
                 py::arg("restraintmask") = "",
                 py::arg("restraint_wt") = 0.0,
                 py::arg("nstlim") = 5000,
                 py::arg("cut") = 8.0,
                 py::arg("ntb") = 1,
                 py::arg("ntc") = 2,
                 py::arg("ntf") = 2,
                 py::arg("tautp") = 1.0,
                 py::arg("taup") = 1.0,
                 py::arg("mcbarint") = 100,
                 py::arg("gamma_ln") = 5.0,
                 py::arg("dt") = 0.002,
                 py::arg("nscm") = 0,
                 py::arg("ntwx") = 500,
                 py::arg("ntpr") = 50,
                 py::arg("ntwr") = 500)
            .def("Run", &Md::Run)
            .def("setCut", &Md::setCut)
            .def("setTemp", &Md::setTemp)
            .def("setNTpr", &Md::setNTpr)
            .def("setNTwx", &Md::setNTwx)
            .def("setNTwr", &Md::setNTwr)
            .def("setNstLim", &Md::setNstLim)
            .def("setIrest", &Md::setIrest)
            .def("setTautp", &Md::setTautp)
            .def("settaup", &Md::settaup)
            .def("setMcbarint", &Md::setMcbarint)
            .def("setGammaLn", &Md::setGammaLn)
            .def("setDt", &Md::setDt)
            .def("setNscm", &Md::setNscm)
            .def("setNtx", &Md::setNtx)
            .def("setNtc", &Md::setNtc)
            .def("setNtf", &Md::setNtf)
            .def("setNtb", &Md::setNtb)
            .def("setBarostat", &Md::setBarostat)
            .def("setThermostat", &Md::setThermostat)
            .def("setRestraintMask",&Md::setRestraintMask);
    py::class_<Nvt>(m, "Nvt", py::dynamic_attr())
            .def(py::init<const std::string &,
                          SystemInfo,
                          const std::string &,
                          const std::string &,
                          bool,
                          float,
                          const std::string &,
                          float,
                          int,
                          float,
                          int,
                          int,
                          float,
                          float,
                          float,
                          int,
                          int,
                          int,
                          int>(),
                 py::arg("name"),
                 py::arg("systemInfo"),
                 py::arg("ref"),
                 py::arg("refc"),
                 py::arg("irest") = false,
                 py::arg("temp") = 303.15,
                 py::arg("restraintmask") = "",
                 py::arg("restraint_wt") = 0.0,
                 py::arg("nstlim") = 5000,
                 py::arg("cut") = 8.0,
                 py::arg("ntc") = 2,
                 py::arg("ntf") = 2,
                 py::arg("tautp") = 1.0,
                 py::arg("gamma_ln") = 5.0,
                 py::arg("dt") = 0.002,
                 py::arg("nscm") = 0,
                 py::arg("ntwx") = 500,
                 py::arg("ntpr") = 50,
                 py::arg("ntwr") = 500)
            .def("Run", &Nvt::Run)
            .def("setCut", &Nvt::setCut)
            .def("setTemp", &Nvt::setTemp)
            .def("setNTpr", &Nvt::setNTpr)
            .def("setNTwx", &Nvt::setNTwx)
            .def("setNTwr", &Nvt::setNTwr)
            .def("setNstLim", &Nvt::setNstLim)
            .def("setIrest", &Nvt::setIrest)
            .def("setTautp", &Nvt::setTautp)
            .def("setGammaLn", &Nvt::setGammaLn)
            .def("setDt", &Nvt::setDt)
            .def("setNscm", &Nvt::setNscm)
            .def("setNtx", &Nvt::setNtx)
            .def("setNtc", &Nvt::setNtc)
            .def("setNtf", &Nvt::setNtf)
            .def("setNtb", &Nvt::setNtb)
            .def("setThermostat", &Nvt::setThermostat)
            .def("setRestraintMask",&Nvt::setRestraintMask);
    py::class_<Npt>(m, "Npt", py::dynamic_attr())
            .def(py::init<const std::string &,
                          SystemInfo,
                          const std::string &,
                          const std::string &,
                          bool,
                          float,
                          const std::string &,
                          float,
                          int,
                          float,
                          int,
                          int,
                          float,
                          float,
                          int,
                          float,
                          float,
                          int,
                          int,
                          int,
                          int>(),
                 py::arg("name"),
                 py::arg("systemInfo"),
                 py::arg("ref"),
                 py::arg("refc"),
                 py::arg("irest") = false,
                 py::arg("temp") = 303.15,
                 py::arg("restraintmask") = "",
                 py::arg("restraint_wt") = 0.0,
                 py::arg("nstlim") = 5000,
                 py::arg("cut") = 8.0,
                 py::arg("ntc") = 2,
                 py::arg("ntf") = 2,
                 py::arg("tautp") = 1.0,
                 py::arg("taup") = 1.0,
                 py::arg("mcbarint") = 100,
                 py::arg("gamma_ln") = 5.0,
                 py::arg("dt") = 0.002,
                 py::arg("nscm") = 0,
                 py::arg("ntwx") = 500,
                 py::arg("ntpr") = 50,
                 py::arg("ntwr") = 500)
            .def("Run", &Npt::Run)
            .def("setCut", &Npt::setCut)
            .def("setTemp", &Npt::setTemp)
            .def("setNTpr", &Npt::setNTpr)
            .def("setNTwx", &Npt::setNTwx)
            .def("setNTwr", &Npt::setNTwr)
            .def("setNstLim", &Npt::setNstLim)
            .def("setIrest", &Npt::setIrest)
            .def("setTautp", &Npt::setTautp)
            .def("setTaup", &Npt::settaup)
            .def("setMcbarint", &Npt::setMcbarint)
            .def("setGammaLn", &Npt::setGammaLn)
            .def("setDt", &Npt::setDt)
            .def("setNscm", &Npt::setNscm)
            .def("setNtx", &Npt::setNtx)
            .def("setNtc", &Npt::setNtc)
            .def("setNtf", &Npt::setNtf)
            .def("setBarostat", &Npt::setBarostat)
            .def("setThermostat", &Npt::setThermostat)
            .def("setRestraintMask",&Npt::setRestraintMask);
    py::class_<GaMd>(m, "GaMd", py::dynamic_attr())
            .def(py::init<const std::string &,
                          SystemInfo,
                          const std::string &,
                          const std::string &,
                          bool,
                          float,
                          const std::string &,
                          float,
                          int,
                          float,
                          int,
                          int,
                          float,
                          float,
                          int,
                          float,
                          float,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          int,
                          float,
                          float,
                          std::string,
                          std::string>(),
                 py::arg("name"),
                 py::arg("systemInfo"),
                 py::arg("ref"),
                 py::arg("refc"),
                 py::arg("irest") = false,
                 py::arg("temp") = 303.15,
                 py::arg("restraintmask") = "",
                 py::arg("restraint_wt") = 0.0,
                 py::arg("nstlim") = 5000,
                 py::arg("cut") = 8.0,
                 py::arg("ntc") = 2,
                 py::arg("ntf") = 2,
                 py::arg("tautp") = 1.0,
                 py::arg("taup") = 1.0,
                 py::arg("mcbarint") = 100,
                 py::arg("gamma_ln") = 5.0,
                 py::arg("dt") = 0.002,
                 py::arg("nscm") = 0,
                 py::arg("ntwx") = 500,
                 py::arg("ntpr") = 50,
                 py::arg("ntwr") = 500,
                 py::arg("igamd") = 0,
                 py::arg("ie") = 1,
                 py::arg("iep") = 1,
                 py::arg("ied") = 1,
                 py::arg("ntcmdprep") = 200000,
                 py::arg("ntcmd") = 1000000,
                 py::arg("ntebprep") = 200000,
                 py::arg("nteb") = 1000000,
                 py::arg("ntave") = 50000,
                 py::arg("irest_gamd") = 0,
                 py::arg("sigma0P") = 6.0,
                 py::arg("sigma0D") = 6.0,
                 py::arg("timask1") = "",
                 py::arg("scmask1") = "")
            .def("Run", &GaMd::Run)
            .def("setCut", &GaMd::setCut)
            .def("setTemp", &GaMd::setTemp)
            .def("setNTpr", &GaMd::setNTpr)
            .def("setNTwx", &GaMd::setNTwx)
            .def("setNTwr", &GaMd::setNTwr)
            .def("setNstLim", &GaMd::setNstLim)
            .def("setIrest", &GaMd::setIrest)
            .def("setTautp", &GaMd::setTautp)
            .def("setTaup", &GaMd::settaup)
            .def("setMcbarint", &GaMd::setMcbarint)
            .def("setGammaLn", &GaMd::setGammaLn)
            .def("setDt", &GaMd::setDt)
            .def("setNscm", &GaMd::setNscm)
            .def("setNtx", &GaMd::setNtx)
            .def("setNtc", &GaMd::setNtc)
            .def("setNtf", &GaMd::setNtf)
            .def("setBarostat", &GaMd::setBarostat)
            .def("setThermostat", &GaMd::setThermostat)
            .def("setRestraintMask",&GaMd::setRestraintMask)
            .def("setIGaMd",&GaMd::setIGaMd)
            .def("setIe",&GaMd::setIe)
            .def("setIep",&GaMd::setIep)
            .def("setIed",&GaMd::setIed)
            .def("setNtcmdprep",&GaMd::setNtcmdprep)
            .def("setNteb",&GaMd::setNteb)
            .def("setNtave",&GaMd::setNtave)
            .def("setIrest_gamd",&GaMd::setIrest_gamd)
            .def("setSigma0P",&GaMd::setSigma0P)
            .def("setSigmaOD",&GaMd::setSigmaOD)
            .def("setTimask1",&GaMd::setTimask1)
            .def("setScmask1",&GaMd::setScmask1);
}
