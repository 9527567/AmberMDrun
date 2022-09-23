//
// Created by jack on 2022/9/19.
//

#ifndef AMBERMD_BASE_HPP
#define AMBERMD_BASE_HPP
#include "SystemInfo.hpp"
#include <string>
class Base
{
public:
    explicit Base(std::string name,SystemInfo systemInfo, float cut = 8.0);
    Base() = default;
    ~Base() = default;
    virtual void operator()(float cut = 8.0);
    virtual void Run();
    SystemInfo systemInfo_;
protected:
    virtual void writeInput();
    virtual void charmmWater();
    virtual void restraint();
    virtual void writeEnd();
    std::string name_;
    int iMin_{};
    float cut_{8.0};
    std::string restraintMask;
    int nTwx_{};
    int nTwr_{};
    int nTpr_{};
    bool hasCharmmWater_{false};
};
#endif//AMBERMD_BASE_HPP
