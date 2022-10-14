//
// Created by jack on 2022/9/19.
//

#ifndef AMBERMD_BASE_HPP
#define AMBERMD_BASE_HPP
#include "SystemInfo.hpp"
#include "common.hpp"
#include <memory>
#include <string>
class Base
{
public:
    Base(const std::string &name, SystemInfo systemInfo, const std::string &ref, bool iRest = false, const std::string &restrintmask = "", float restrant_wt = 0.0, float cut = 8.0);
    Base() = default;
    ~Base() = default;
    virtual void operator()(float cut = 8.0);
    virtual void Run();
    SystemInfo systemInfo_;
    [[maybe_unused]] virtual Base *setCut(float cut);
    [[maybe_unused]] virtual Base *setNTwx(int ntwx);
    [[maybe_unused]] virtual Base *setNTwr(int ntwr);
    [[maybe_unused]] virtual Base *setNTpr(int ntpr);
    [[maybe_unused]] virtual void appendMask(std::string mask);

protected:
    virtual void setRestraintMask(std::string);
    virtual void writeInput();
    virtual void charmmWater();
    virtual void restraint();
    virtual void runMd();
    virtual void writeEnd();
    std::string name_;
    int iMin_;
    float cut_;
    bool iRest_;
    std::string ref_;
    std::string restraintMask_;
    float restraint_wt_;
    int nTwx_;
    int nTwr_;
    int nTpr_;
    bool hasCharmmWater_{false};
};
#endif//AMBERMD_BASE_HPP
