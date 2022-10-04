add_requires("cmake::pybind11")
target("AmberMD")
    set_kind("binary")
    add_includedirs("include")
    add_files("src/*.cpp")
    add_files("src/*.cc")
    add_files("main.cpp")



