//
// Created by jack on 2022/12/7.
//

#ifndef NVT_HPP
#define NVT_HPP
#include "md.hpp"
class Nvt : public Md
{
public:
    Nvt(const std::string &name, SystemInfo systemInfo, const std::string &rst7, const std::string &refc, bool irest = false, float temp = 303.15, const std::string &restraintmask = "", float restraint_wt = 0.0, int nstlim = 5000, float cut = 8.0, int ntc = 2, int ntf = 2, float gamma_ln = 5.0, float tautp = 1.0, float dt = 0.002, int nscm = 0, int ntwx = 500, int ntpr = 50, int ntwr = 500);
    ~Nvt() = default;
    void Run() override;
    Nvt *setCut(float cut) override;
    Nvt *setNTpr(int ntpr) override;
    Nvt *setNTwx(int ntwx) override;
    Nvt *setNTwr(int ntwr) override;
    Nvt *setNstLim(int nstlim) override;
    Nvt *setIrest(bool irest) override;
    Nvt *setTautp(float tautp) override;
    Nvt *setGammaLn(float gamma_ln) override;
    Nvt *setDt(float dt) override;
    Nvt *setNscm(int nscm) override;
    Nvt *setNtx(int ntx) override;
    Nvt *setNtc(int ntc) override;
    Nvt *setNtf(int ntf) override;
    Nvt *setTemp(float temp) override;
    Nvt *setThermostat(const std::string &) override;
    Nvt *setRestraintMask(std::string) override;
    Nvt *setRestraint_wt(float) override;

protected:
    void writeInput() override;
    void charmmWater() override;
    void restraint() override;
    void writeEnd() override;
    void runMd() override;
    void Thermostat() override;
};
#endif//NVT_HPP
