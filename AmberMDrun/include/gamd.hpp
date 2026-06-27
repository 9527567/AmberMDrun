#ifndef AMBERMD_GAMD_HPP
#define AMBERMD_GAMD_HPP
#include "npt.hpp"

/// @brief Gaussian accelerated MD (GaMD) step.
///
/// Extends Npt with GaMD-specific parameters: igamd, sigma0P/D,
/// dual-boost settings, and timask1/scmask1 atom masks.
/// Inherits Npt constructors via `using Npt::Npt`.
class GaMd : public Npt
{
public:
    using Npt::Npt;
    /// @param name        Step name
    /// @param systemInfo  Topology/system information
    /// @param rst7        Input coordinate file
    /// @param refc        Reference coordinate for restraints
    /// @param irest       Restart flag
    /// @param temp        Simulation temperature (K)
    /// @param restraintmask  Amber atom mask
    /// @param restraint_wt   Restraint force constant
    /// @param nstlim      Number of MD steps
    /// @param cut         Non-bonded cutoff
    /// @param ntc         SHAKE constraint
    /// @param ntf         Force evaluation
    /// @param tautp       Thermostat time constant
    /// @param taup        Barostat time constant
    /// @param mcbarint    MC barostat interval
    /// @param gamma_ln    Langevin collision frequency
    /// @param dt          Time step (ps)
    /// @param nscm        COM removal frequency
    /// @param ntwx        Trajectory output frequency
    /// @param ntpr        Print frequency
    /// @param ntwr        Restart frequency
    /// @param igamd       GaMD mode (0=off, 1=dual, 2=dihedral, 3=total)
    /// @param ie          GaMD boost potential type
    /// @param iep         Potential energy boost flag
    /// @param ied         Dihedral energy boost flag
    /// @param ntcmdprep  Number of GaMD prep steps
    /// @param ntcmd       Number of GaMD steps after prep
    /// @param ntebprep   Number of equilibration prep steps
    /// @param nteb        Number of equilibration steps
    /// @param ntave       Averaging steps for sigma
    /// @param irest_gamd  GaMD restart flag
    /// @param sigma0P     Upper limit of potential sigma (kcal/mol)
    /// @param sigma0D     Upper limit of dihedral sigma (kcal/mol)
    /// @param timask1     Atom mask for GaMD
    /// @param scmask1     SCP mask for GaMD
    GaMd(const std::string &name, SystemInfo systemInfo, const std::string &rst7, const std::string &refc, bool irest = false, float temp = 303.15, const std::string &restraintmask = "", float restraint_wt = 0.0, int nstlim = 5000, float cut = 8.0, int ntc = 2, int ntf = 2, float tautp = 1.0, float taup = 1.0, int mcbarint = 100, float gamma_ln = 5.0, float dt = 0.002, int nscm = 0, int ntwx = 500, int ntpr = 50, int ntwr = 500, int igamd = 0, int ie = 1, int iep = 1, int ied = 1, int ntcmdprep = 200000, int ntcmd = 100000, int ntebprep = 200000, int nteb = 1000000, int ntave = 50000, int irest_gamd = 0, float sigma0P = 6.0, float sigma0D = 6.0, std::string timask1 = "", std::string scmask1 = "");
    ~GaMd() = default;
    void Run() override;
    GaMd *setCut(float cut) override;
    GaMd *setNTpr(int ntpr) override;
    GaMd *setNTwx(int ntwx) override;
    GaMd *setNTwr(int ntwr) override;
    GaMd *setNstLim(int nstlim) override;
    GaMd *setIrest(bool irest) override;
    GaMd *setTautp(float tautp) override;
    GaMd *settaup(float taup) override;
    GaMd *setMcbarint(int mcbarint) override;
    GaMd *setGammaLn(float gamma_ln) override;
    GaMd *setDt(float dt) override;
    GaMd *setNscm(int nscm) override;
    GaMd *setNtx(int ntx) override;
    GaMd *setNtc(int ntc) override;
    GaMd *setNtf(int ntf) override;
    GaMd *setTemp(float temp) override;
    GaMd *setBarostat(const std::string &) override;
    GaMd *setThermostat(const std::string &) override;
    GaMd *setRestraintMask(std::string) override;
    GaMd *setRestraint_wt(float) override;
    GaMd *setIGaMd(int);
    GaMd *setIe(int);
    GaMd *setIep(int);
    GaMd *setIed(int);
    GaMd *setNtcmdprep(int);
    GaMd *setNteb(int);
    GaMd *setNtave(int);
    GaMd *setIrest_gamd(int);
    GaMd *setSigma0P(float);
    GaMd *setSigmaOD(float);
    GaMd *setTimask1(std::string);
    GaMd *setScmask1(std::string);

protected:
    void writeInput() override;
    void charmmWater() override;
    void restraint() override;
    void writeEnd() override;
    void runMd() override;
    void barostat() override;
    void Thermostat() override;
    int igamd_ = 0;
    int ie_ = 1;
    int iep_ = 1;
    int ied_ = 1;
    int ntcmdprep_ = 200000;
    int ntcmd_ = 1000000;
    int ntebprep_ = 200000;
    int nteb_ = 1000000;
    int ntave_ = 50000;
    int irest_gamd_ = 0;
    float sigma0P_ = 6.0;
    float sigma0D_ = 6.0;
    std::string timask1_{};
    std::string scmask1_ = {};
};
#endif//AMBERMD_GAMD_HPP
