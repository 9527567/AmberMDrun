//
// Created by jack on 2022/9/19.
//

#ifndef AMBERMD_BASE_HPP
#define AMBERMD_BASE_HPP
#include <memory>
#include <string>
#if __cplusplus >= 202002L
#include <semaphore>
using binary_semaphore = std::binary_semaphore;
#else
#include "semaphore.hpp"
using binary_semaphore = yamc::posix::binary_semaphore;
#endif
#include <thread>
#include "SystemInfo.hpp"
#include "common.hpp"
#include "tqdm.hpp"
#include "fswatch.hpp"

class Base
{
public:
    Base(const std::string &name, SystemInfo systemInfo, const std::string &rst7, const std::string &refc, bool iRest = false, const std::string &restrintmask = "", float restrant_wt = 0.0, float cut = 8.0);
    Base() = default;
    ~Base() = default;
    virtual void Run();
    SystemInfo systemInfo_;
    [[maybe_unused]] virtual Base *setCut(float cut);
    [[maybe_unused]] virtual Base *setNTwx(int ntwx);
    [[maybe_unused]] virtual Base *setNTwr(int ntwr);
    [[maybe_unused]] virtual Base *setNTpr(int ntpr);
    virtual Base *setRestraintMask(std::string);
    virtual Base *setRestraint_wt(float);

protected:
    virtual void writeInput();
    virtual void charmmWater();
    virtual void restraint();
    virtual void runMd();
    virtual void progress();
    virtual void writeEnd();
    binary_semaphore run_{0}, pro_{0};
    std::string name_;
    bool done_ = false;
    int iMin_;
    float cut_;
    bool iRest_;
    std::string rst7_;
    std::string refc_;
    std::string restraintMask_;
    float restraint_wt_;
    int nTwx_;
    int nTwr_;
    int nTpr_;
    bool hasCharmmWater_{false};
};
#endif//AMBERMD_BASE_HPP
