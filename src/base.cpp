//
// Created by jack on 2022/9/19.
//
#include "base.hpp"

#include "fmt/core.h"
#include "fmt/os.h"
#include <utility>
Base::Base(std::string name,SystemInfo systemInfo, float cut) : name_(std::move(name)), systemInfo_(systemInfo), cut_(cut)
{
}
void Base::operator()(float cut)
{
}
void Base::writeInput()
{
    fmt::ostream out = fmt::output_file(name_ + ".in");
    out.print("Minimization: " + name_ + "\n");
    out.print("&cntrl\n");
}
void Base::Run()
{
    writeInput();
    charmmWater();
    restraint();
    writeEnd();
}
void Base::charmmWater()
{
    if (systemInfo_.getHasCharmmWater())
    {
        hasCharmmWater_ = true;
    }
    if (hasCharmmWater_)
    {
        fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
        out.print("   WATNAM = 'TIP3', OWTNM = 'OH2',");
    }
}
void Base::writeEnd()
{
    fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
    out.print("&end\n");
}
void Base::restraint()
{

}

