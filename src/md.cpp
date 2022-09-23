//
// Created by jack on 2022/9/21.
//
#include "md.hpp"
Md::Md(std::string name, SystemInfo systemInfo, int nstlim, bool irest, int ntb, float tautp, float taup, int mcbarint, int gamma_ln, float dt, int nscm, int ntwx, int ntpr, int ntwr) : Base(name, systemInfo)
{
    name_ = name;
    nstLim_ = nstlim;
    iRest_ = irest;
    ntb_ = ntb;
    tautp_ = tautp;
    taup_ = taup;
    mcbarint_ = mcbarint;
    gamma_ln_ = gamma_ln;
    dt_ = dt;
    nscm_ = nscm;
    ntwx_ = ntwx;
    ntpr_ = ntpr;
    ntwr_ = ntwr;
}
void Md::operator()(std::string name, int nstlim, bool irest, int ntb, float tautp, float taup, int mcbarint, int gamma_ln, float dt, int nscm, int ntwx, int ntpr, int ntwr)
{
    name_ = name;
    nstLim_ = nstlim;
    iRest_ = irest;
    ntb_ = ntb;
    tautp_ = tautp;
    taup_ = taup;
    mcbarint_ = mcbarint;
    gamma_ln_ = gamma_ln;
    dt_ = dt;
    nscm_ = nscm;
    ntwx_ = ntwx;
    ntpr_ = ntpr;
    ntwr_ = ntwr;
}
void Md::Run()
{
    Base::Run();
}
void Md::writeInput()
{
    Base::writeInput();
}
void Md::charmmWater()
{
    Base::charmmWater();
}
void Md::restraint()
{
    Base::restraint();
}
void Md::writeEnd()
{
    Base::writeEnd();
}
