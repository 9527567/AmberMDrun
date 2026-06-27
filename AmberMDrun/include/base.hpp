#ifndef AMBERMD_BASE_HPP
#define AMBERMD_BASE_HPP
#include <memory>
#include <string>
#include <atomic>
#include <csignal>
#include <thread>
#include <chrono>
#if __cplusplus >= 202002L
#include <semaphore>
using binary_semaphore = std::binary_semaphore;
#else
#include "semaphore.hpp"
using binary_semaphore = yamc::posix::binary_semaphore;
#endif
#include "SystemInfo.hpp"
#include "common.hpp"
#include "tqdm.hpp"
#include "fswatch.hpp"

/// @brief Abstract base class for all Amber MD simulation steps.
///
/// Provides the core dual-thread execution pattern: one thread runs the
/// Amber engine, another monitors .out file changes for progress display.
/// Subclasses override writeInput() to produce step-specific Amber input files.
class Base
{
public:
    /// @param name       Step name (used for .in, .out, .rst7 filenames)
    /// @param systemInfo Topology/system information
    /// @param rst7       Input coordinate file (.rst7 or .inpcrd)
    /// @param refc       Reference coordinate for restraints
    /// @param iRest      Restart from previous run (irest=1)
    /// @param restraintmask Amber atom mask for restraints
    /// @param restraint_wt  Restraint force constant (kcal/mol/A^2)
    /// @param cut        Non-bonded cutoff (A)
    Base(const std::string &name, SystemInfo systemInfo, const std::string &rst7, const std::string &refc, bool iRest = false, const std::string &restrintmask = "", float restrant_wt = 0.0, float cut = 8.0);
    Base() = default;
    virtual ~Base() = default;

    /// @brief Write Amber input, launch two threads (engine + progress), wait for completion.
    ///        Installs SIGINT handler to allow Ctrl+C termination.
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
    binary_semaphore run_{0};
    std::string name_;
    std::atomic<bool> done_{false};
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
    int childPid_ = -1;
    static Base *runningInstance_;
    static void sigintHandler(int);
};
#endif//AMBERMD_BASE_HPP
