cmake_minimum_required(VERSION 3.15.0)
project(AmberMD LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
include_directories(include)
include_directories(extern)
add_subdirectory(extern/pybind11)
aux_source_directory(src SOURCE)
add_library(ambermd SHARED ${SOURCE})
add_executable(amberMd
        main.cpp
        )
target_link_libraries(amberMd PRIVATE ambermd)
pybind11_add_module(_pyamber
        pyamber.cpp
        )
target_link_libraries(_pyamber PRIVATE ambermd)