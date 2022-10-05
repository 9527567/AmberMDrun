add_requires("pybind11")
target("amber")
    set_kind("shared")
    add_packages("pybind11")
    add_includedirs("include")
    add_files("src/*.cpp")
    add_files("src/*.cc")
    add_files("pyamber.cpp")

target("AmberMD")
    set_kind("binary")
    add_includedirs("include")
    add_files("src/*.cpp")
    add_files("src/*.cc")
    add_files("main.cpp")




