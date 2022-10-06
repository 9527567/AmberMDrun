//
// Created by jack on 2022/10/4.
//
#include "md.hpp"
#include "min.hpp"
#include "pybind11/pybind11.h"
namespace py = pybind11;
PYBIND11_MODULE(pyamber, m)
{
    py::class_<SystemInfo>(m, "SystemInfo")
            .def(py::init<const std::string &>())
            .def("getNprotein", &SystemInfo::getNprotein)
            .def("getnDna", &SystemInfo::getnDna)
            .def("getnRna", &SystemInfo::getnRna)
            .def("getnLipid", &SystemInfo::getnLipid)
            .def("getnUnKnown_", &SystemInfo::getnUnKnown_)
            .def("getnCharmmWater_", &SystemInfo::getnCharmmWater_)
            .def("getnWater", &SystemInfo::getnWater)
            .def("getnCarbo", &SystemInfo::getnCarbo)
            .def("getHasCharmmWater", &SystemInfo::getHasCharmmWater);

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
            .def(py::init<std::string,
                          SystemInfo,
                          std::string,
                          float,
                          float,
                          int, int,
                          int, int,
                          int,
                          int>(),
                 py::arg("name"),
                 py::arg("symstemInfo"),
                 py::arg("restrintmask") = "",
                 py::arg("restrant_wt") = 0.0,
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
            .def("Run", &Min::Run);
    py::class_<Md>(m, "Md", py::dynamic_attr())
            .def(py::init<const std::string &,
                          SystemInfo,
                          float,
                          std::string,
                          float,
                          int,
                          float,
                          bool,
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
                 py::arg("systeminfo"),
                 py::arg("temp"),
                 py::arg("restrintmask"),
                 py::arg("restrant_wt") = 0.0,
                 py::arg("nstlim") = 5000,
                 py::arg("cut") = 8.0,
                 py::arg("irest") = false,
                 py::arg("ntb") = 1,
                 py::arg("ntc") = 2,
                 py::arg("ntf") = 2,
                 py::arg("tautp") = 1.0,
                 py::arg("taup") = 1.0,
                 py::arg("mcbarint") = 100,
                 py::arg("gamma_ln") = 5.0,
                 py::arg("dt") = 0.002,
                 py::arg("ncsm") = 0,
                 py::arg("ntwx") = 500,
                 py::arg("ntpr") = 50,
                 py::arg("ntwr") = 500)
            .def("Run", &Md::Run)
            .def("setCut", &Md::setCut)
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
            .def("setThermostat", &Md::setThermostat);
}
