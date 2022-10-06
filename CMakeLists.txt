cmake_minimum_required(VERSION 3.15.0)
project(AmberMD LANGUAGES CXX)
include_directories(include)
include_directories(extern)
add_subdirectory(extern/pybind11)
aux_source_directory(src SOURCE)
add_library(ambermd SHARED ${SOURCE})
add_executable(AmberMD
        main.cpp
        )
target_link_libraries(AmberMD PRIVATE ambermd)
pybind11_add_module(pyamber
        pyamber.cpp
        )
target_link_libraries(pyamber PRIVATE ambermd)