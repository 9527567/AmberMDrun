//
// Created by jack on 2022/9/21.
//

#ifndef AMBERMD_MD_HPP
#define AMBERMD_MD_HPP
#include "base.hpp"
class Md : Base
{
public:
    Md(const std::string &name, SystemInfo systemInfo, const std::string &ref, bool irest = false, float temp = 303.15, const std::string &restraintmask = "", float restraint_wt = 0.0, int nstlim = 5000, float cut = 8.0, int ntb = 1, int ntc = 2, int ntf = 2, float tautp = 1.0, float taup = 1.0, int mcbarint = 100, float gamma_ln = 5.0, float dt = 0.002, int nscm = 0, int ntwx = 500, int ntpr = 50, int ntwr = 500);
    ~Md() = default;
    void operator()(std::string name, int nstlim = 5000, bool irest = false, int ntb = 1, int ntc = 2, int ntf = 2, float tautp = 1.0, float taup = 1.0, int mcbarint = 100, float gamma_ln = 5.0, float dt = 0.001, int nscm = 0, int ntwx = 500, int ntpr = 50, int ntwr = 500);
    void Run() override;
    Md *setCut(float cut) override;
    Md *setNTpr(int ntpr) override;
    Md *setNTwx(int ntwx) override;
    Md *setNTwr(int ntwr) override;
    Md *setNstLim(int nstlim);
    Md *setIrest(bool irest);
    Md *setTautp(float tautp);
    Md *settaup(float taup);
    Md *setMcbarint(int mcbarint);
    Md *setGammaLn(float gamma_ln);
    Md *setDt(float dt);
    Md *setNscm(int nscm);
    Md *setNtx(int ntx);
    Md *setNtc(int ntc);
    Md *setNtf(int ntf);
    Md *setNtb(int ntb);
    Md *setTemp(float temp);
    Md *setBarostat(std::string baroType);
    Md *setThermostat(std::string thermoType);

protected:
    void setRestraintMask(std::string) override;
    void writeInput() override;
    void charmmWater() override;
    void restraint() override;
    void writeEnd() override;
    void runMd() override;
    void barostat();
    void Thermostat();
    int nstLim_;
    bool iRest_;
    float tautp_;
    float taup_;
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
    const int iOutfm_ = 1;
    const int nTxo_ = 2;
    const int iMin_ = 0;
};
#endif//AMBERMD_MD_HPP
