//
// Created by jack on 2022/12/7.
//

#ifndef NPT_HPP
#define NPT_HPP
#include "md.hpp"
class Npt : public Md
{
public:
    Npt() = default;
    Npt(const std::string &name, SystemInfo systemInfo, const std::string &rst7, const std::string &refc, bool irest = false, float temp = 303.15, const std::string &restraintmask = "", float restraint_wt = 0.0, int nstlim = 5000, float cut = 8.0, int ntc = 2, int ntf = 2, float tautp = 1.0, float taup = 1.0, int mcbarint = 100, float gamma_ln = 5.0, float dt = 0.002, int nscm = 0, int ntwx = 500, int ntpr = 50, int ntwr = 500);
    ~Npt() = default;
    void Run() override;
    Npt *setCut(float cut) override;
    Npt *setNTpr(int ntpr) override;
    Npt *setNTwx(int ntwx) override;
    Npt *setNTwr(int ntwr) override;
    Npt *setNstLim(int nstlim) override;
    Npt *setIrest(bool irest) override;
    Npt *setTautp(float tautp) override;
    Npt *settaup(float taup) override;
    Npt *setMcbarint(int mcbarint) override;
    Npt *setGammaLn(float gamma_ln) override;
    Npt *setDt(float dt) override;
    Npt *setNscm(int nscm) override;
    Npt *setNtx(int ntx) override;
    Npt *setNtc(int ntc) override;
    Npt *setNtf(int ntf) override;
    Npt *setTemp(float temp) override;
    Npt *setBarostat(const std::string &) override;
    Npt *setThermostat(const std::string &) override;
    Npt *setRestraintMask(std::string) override;
    Npt *setRestraint_wt(float) override;

protected:
    void writeInput() override;
    void charmmWater() override;
    void restraint() override;
    void writeEnd() override;
    void runMd() override;
    void barostat() override;
    void Thermostat() override;
};
#endif//NPT_HPP
