//
// Created by jack on 2022/9/19.
//

#ifndef AMBERMD_BASE_HPP
#define AMBERMD_BASE_HPP
#include "SystemInfo.hpp"
#include <memory>
#include <string>
class Base
{
public:
    Base(std::string name, SystemInfo systemInfo, std::string restrintmask = "", float restrant_wt = 0.0, float cut = 8.0);
    Base() = default;
    ~Base() = default;
    virtual void operator()(float cut = 8.0);
    virtual void Run();
    SystemInfo systemInfo_;
    virtual Base *setCut(float cut);
    virtual Base* setNTwx(int ntwx);
    virtual Base* setNTwr(int ntwr);
    virtual Base* setNTpr(int ntpr);
    virtual void appendMask(std::string mask);

protected:
    virtual void setRestraintMask(std::string);
    virtual void writeInput();
    virtual void charmmWater();
    virtual void restraint();
    virtual void writeEnd();
    std::string name_;
    int iMin_{};
    float cut_;
    std::string restraintMask_;
    float restraint_wt_;
    int nTwx_;
    int nTwr_;
    int nTpr_;
    bool hasCharmmWater_{false};
};
#endif//AMBERMD_BASE_HPP
