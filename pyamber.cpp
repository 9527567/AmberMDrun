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
            .def(py::init<std::string, SystemInfo, std::string, float, float, int, int, int, int, int, int>())
            .def("setCut", &Min::setCut)
            .def("setNTpr", &Min::setNTpr)
            .def("setNTwr", &Min::setNTwr)
            .def("setNTwx", &Min::setNTwx)
            .def("setMaxCyc", &Min::setMaxCyc)
            .def("setNCyc", &Min::setNCyc)
            .def("setNTim", &Min::setNTim);
}
