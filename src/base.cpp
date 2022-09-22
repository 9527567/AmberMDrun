//
// Created by jack on 2022/9/19.
//
#include "base.hpp"

#include <utility>
#include "fmt/core.h"
#include "fmt/os.h"
Base::Base(std::string name,float cut):name_(std::move(name)),cut_(cut)
{
}
void Base::operator()(float cut)
{
}
void Base::writeInput()
{
    fmt::ostream out = fmt::output_file(name_+".in");
    out.print("Minimization: "+name_+"\n");
    out.print("&cntrl\n");

}

