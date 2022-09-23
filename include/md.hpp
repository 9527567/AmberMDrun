//
// Created by jack on 2022/9/21.
//

#ifndef AMBERMD_MD_HPP
#define AMBERMD_MD_HPP
#include "base.hpp"
class Md : Base
{
public:
    Md(std::string name,SystemInfo systemInfo,int nstlim = 5000, bool irest = false, int ntb = 1, float tautp = 1.0, float taup = 1.0, int mcbarint = 100, int gamma_ln = 5, float dt = 0.001, int nscm = 0, int ntwx = 500, int ntpr = 50, int ntwr = 500);
    ~Md() = default;
    void operator()(std::string name,int nstlim = 5000, bool irest = false, int ntb = 1, float tautp = 1.0, float taup = 1.0, int mcbarint = 100, int gamma_ln = 5, float dt = 0.001, int nscm = 0, int ntwx = 500, int ntpr = 50, int ntwr = 500);
    void Run() override;
protected:
    void writeInput() override;
    void charmmWater() override;
    void restraint() override;
    void writeEnd() override;
    int nstLim_;
    bool iRest_;
    int ntb_;
    float tautp_;
    float taup_;
    int mcbarint_;
    int gamma_ln_;
    float dt_;
    int nscm_;
    int ntwx_;
    int ntpr_;
    int ntwr_;
};
#endif//AMBERMD_MD_HPP
