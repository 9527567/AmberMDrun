//
// Created by jack on 2022/9/21.
//

#ifndef AMBERMD_MIN_HPP
#define AMBERMD_MIN_HPP
#include "base.hpp"
class Min : public Base
{
public:
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
