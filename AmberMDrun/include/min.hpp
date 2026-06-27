#ifndef AMBERMD_MIN_HPP
#define AMBERMD_MIN_HPP
#include "base.hpp"

/// @brief Energy minimization step (imin=1).
///
/// Writes Amber input with imin=1, ntmin/maxcyc/ncyc parameters.
/// Progress is tracked by nTpr_ increments against maxCyc_.
class Min : public Base
{
public:
    /// @param name       Step name
    /// @param systemInfo Topology/system information
    /// @param rst7       Input coordinate file
    /// @param refc       Reference coordinate for restraints
    /// @param irest      Restart flag
    /// @param restraintmask  Amber atom mask
    /// @param restraint_wt   Restraint force constant
    /// @param cut        Non-bonded cutoff
    /// @param nTmin      Minimization method (1=steepest descent, 2=conjugate gradient)
    /// @param maxCyc     Maximum number of cycles
    /// @param nCyc       Cycles of steepest descent before switching
    /// @param nTwx       Write trajectory frequency
    /// @param nTpr       Print output frequency
    /// @param nTwr       Write restart frequency
    Min(const std::string &name, SystemInfo systemInfo, const std::string &rst7, const std::string &refc, bool irest = false, const std::string &restrintmask = "", float restrant_wt = 0.0, float cut = 8.0, int nTmin = 2, int maxCyc = 1000, int nCyc = 10, int nTwx = 500, int nTpr = 50, int nTwr = 500);
    ~Min() = default;
    void operator()(std::string name, int nTmin = 2, int maxCyc = 1000, int nCyc = 10, int nTwx = 500, int nTpr = 50, int nTwr = 500);
    void Run() override;
    Min *setCut(float cut) override;
    Min *setNTpr(int ntpr) override;
    Min *setNTwr(int ntwr) override;
    Min *setNTwx(int ntwx) override;
    Min *setMaxCyc(int maxcyc);
    Min *setNCyc(int cyc);
    Min *setNTim(int ntim);
    Min *setRestraintMask(std::string) override;
    Min *setRestraint_wt(float) override;

protected:
    void writeInput() override;
    void charmmWater() override;
    void restraint() override;
    void writeEnd() override;
    void runMd() override;
    void progress() override;
    int nTmin_;
    int maxCyc_;
    int nCyc_;
    const int iOutfm_ = 1;
    const int nTxo_ = 2;
    const int ntc_ = 1;
    const int ntf_ = 1;
    const int ntb_ = 1;
};
#endif//AMBERMD_MIN_HPP
