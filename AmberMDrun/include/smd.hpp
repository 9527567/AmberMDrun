//
// Created by jack on 3/3/23.
//

#ifndef AMBERMDRUN_SMD_H
#define AMBERMDRUN_SMD_H
#include "npt.hpp"
class SMD : public Npt
{
public:
    SMD() = default;
    SMD(const std::string &name, const SystemInfo& systemInfo, const std::string &rst7, const std::string &refc, bool irest = false, float temp = 303.15, const std::string &restraintmask = "", float restraint_wt = 0.0, int nstlim = 5000, float cut = 8.0, int ntc = 2, int ntf = 2, float tautp = 1.0, float taup = 1.0, int mcbarint = 100, float gamma_ln = 5.0, float dt = 0.002, int nscm = 0, int ntwx = 500, int ntpr = 50, int ntwr = 500
        );
    ~SMD() = default;
    void Run() override;
    SMD *setCut(float cut) override;
    SMD *setNTpr(int ntpr) override;
    SMD *setNTwx(int ntwx) override;
    SMD *setNTwr(int ntwr) override;
    SMD *setNstLim(int nstlim) override;
    SMD *setIrest(bool irest) override;
    SMD *setTautp(float tautp) override;
    SMD *settaup(float taup) override;
    SMD *setMcbarint(int mcbarint) override;
    SMD *setGammaLn(float gamma_ln) override;
    SMD *setDt(float dt) override;
    SMD *setNscm(int nscm) override;
    SMD *setNtx(int ntx) override;
    SMD *setNtc(int ntc) override;
    SMD *setNtf(int ntf) override;
    SMD *setTemp(float temp) override;
    SMD *setBarostat(const std::string &) override;
    SMD *setThermostat(const std::string &) override;
    SMD *setRestraintMask(std::string) override;
    SMD *setRestraint_wt(float) override;
private:
    void pull();
};
#endif//AMBERMDRUN_SMD_H
