#ifndef AMBERMD_MD_HPP
#define AMBERMD_MD_HPP
#include <thread>
#include "base.hpp"

/// @brief Molecular dynamics step base class (imin=0).
///
/// Supports NVT and NPT ensembles via thermostat and barostat settings.
/// Produces Amber MD input with nstlim, dt, ntb, ntc, ntf, etc.
class Md : public Base
{
public:
    Md() = default;
    /// @param name        Step name
    /// @param systemInfo  Topology/system information
    /// @param rst7        Input coordinate file
    /// @param refc        Reference coordinate for restraints
    /// @param irest       Restart from previous run
    /// @param temp        Simulation temperature (K)
    /// @param restraintmask  Amber atom mask for restraints
    /// @param restraint_wt   Restraint force constant
    /// @param nstlim      Number of MD steps
    /// @param cut         Non-bonded cutoff (A)
    /// @param ntb         Periodic boundary (1=NVT, 2=NPT)
    /// @param ntc         SHAKE constraint (2=H-bonds)
    /// @param ntf         Force evaluation (2=no H-bond forces)
    /// @param tautp       Thermostat time constant (ps)
    /// @param taup        Barostat time constant (ps)
    /// @param mcbarint    Monte Carlo barostat interval
    /// @param gamma_ln    Langevin collision frequency (1/ps)
    /// @param dt          Time step (ps)
    /// @param nscm        Center-of-mass removal frequency
    /// @param ntwx        Write trajectory frequency
    /// @param ntpr        Print output frequency
    /// @param ntwr        Write restart frequency
    Md(const std::string &name, SystemInfo systemInfo, const std::string &rst7, const std::string &refc, bool irest = false, float temp = 303.15, const std::string &restraintmask = "", float restraint_wt = 0.0, int nstlim = 5000, float cut = 8.0, int ntb = 1, int ntc = 2, int ntf = 2, float tautp = 1.0, float taup = 1.0, int mcbarint = 100, float gamma_ln = 5.0, float dt = 0.002, int nscm = 0, int ntwx = 500, int ntpr = 50, int ntwr = 500);
    ~Md() = default;
    void Run() override;
    Md *setCut(float cut) override;
    Md *setNTpr(int ntpr) override;
    Md *setNTwx(int ntwx) override;
    Md *setNTwr(int ntwr) override;
    virtual Md *setNstLim(int nstlim);
    virtual Md *setIrest(bool irest);
    virtual Md *setTautp(float tautp);
    virtual Md *settaup(float taup);
    virtual Md *setMcbarint(int mcbarint);
    virtual Md *setGammaLn(float gamma_ln);
    virtual Md *setDt(float dt);
    virtual Md *setNscm(int nscm);
    virtual Md *setNtx(int ntx);
    virtual Md *setNtc(int ntc);
    virtual Md *setNtf(int ntf);
    virtual Md *setNtb(int ntb);
    virtual Md *setTemp(float temp);
    /// @brief Set barostat type
    /// @param baroType "berendsen" or "montecarlo"
    virtual Md *setBarostat(const std::string &);
    /// @brief Set thermostat type
    /// @param thermoType "berendsen" or "langevin"
    virtual Md *setThermostat(const std::string &);
    Md *setRestraintMask(std::string) override;
    Md * setRestraint_wt(float) override;

protected:
    void writeInput() override;
    void charmmWater() override;
    void restraint() override;
    void writeEnd() override;
    void runMd() override;
    void progress() override;
    virtual void barostat();
    virtual void Thermostat();
    int nstLim_;
    bool iRest_;
    int mcbarint_;
    float gamma_ln_;
    float dt_;
    int nscm_;
    int ntx_;
    int ntc_;
    int ntf_;
    int ntb_;
    int ntpFlags_;
    float temp_;
    const int iOutfm_ = 1;
    const int nTxo_ = 2;
    const int iMin_ = 0;
    float tautp_;
    float taup_;
    enum class baro { berendsen, montecarlo };
    enum class thermo { berendsen, langevin };
    baro baroType_ = baro::montecarlo;
    thermo thermoType_ = thermo::langevin;
};
#endif//AMBERMD_MD_HPP
