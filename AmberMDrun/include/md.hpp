//
// Created by jack on 2022/9/21.
//

#ifndef AMBERMD_MD_HPP
#define AMBERMD_MD_HPP
#include <thread>
#include "base.hpp"
class Md : public Base
{
public:
    Md() = default;
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
    virtual Md *setBarostat(const std::string &);
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
    enum class baro
    {
        berendsen,
        montecarlo
    };
    enum class thermo
    {
        berendsen,
        langevin
    };
    baro baroType_ = baro::montecarlo;
    thermo thermoType_ = thermo::langevin;
};
#endif//AMBERMD_MD_HPP
