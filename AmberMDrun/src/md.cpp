//
// Created by jack on 2022/9/21.
//
#include "md.hpp"
#include "fmt/os.h"
Md::Md(const std::string &name, SystemInfo systemInfo, const std::string &rst7, const std::string &refc, bool irest, float temp, const std::string &restraintmask, float restraint_wt, int nstlim, float cut, int ntb, int ntc, int ntf, float tautp, float taup, int mcbarint, float gamma_ln, float dt, int nscm, int ntwx, int ntpr, int ntwr)
{
    name_ = name;
    systemInfo_ = systemInfo;
    rst7_ = rst7;
    refc_ = refc;
    iRest_ = irest;
    restraintMask_ = restraintmask;
    restraint_wt_ = restraint_wt;
    cut_ = cut;
    temp_ = temp;
    nstLim_ = nstlim;
    tautp_ = tautp;
    taup_ = taup;
    mcbarint_ = mcbarint;
    gamma_ln_ = gamma_ln;
    dt_ = dt;
    nscm_ = nscm;
    nTwx_ = ntwx;
    nTpr_ = ntpr;
    nTwr_ = ntwr;
    ntb_ = ntb;
    ntc_ = ntc;
    ntf_ = ntf;
    ntpFlags_ = 1;
    if (systemInfo_.getnLipid() != 0 && systemInfo.getHasOrthoBox())
    {
        ntpFlags_ = 2;
    }
    if (iRest_)
    {
        ntx_ = 5;
    } else
    {
        ntx_ = 1;
    }
}
void Md::Run()
{
    if (this->done_) this->done_ = false;
    writeInput();
    charmmWater();
    Thermostat();
    if (ntb_ == 2)
    {
        barostat();
    }
    restraint();
    writeEnd();
    {
        std::thread th1(&Md::progress, this);
        std::thread th2(&Md::runMd, this);
        th1.join();
        th2.join();
    }
}
void Md::writeInput()
{
    fmt::ostream out = fmt::output_file(name_ + ".in");
    out.print("Md:{}\n", name_);
    out.print("&cntrl\n");
    out.print("imin={},", iMin_);
    out.print("nstlim={},", nstLim_);
    out.print("dt={},", dt_);
    out.print("\n");
    out.print("ntx={},", ntx_);
    if (iRest_)
    {
        out.print("irest={},", 1);
    } else
    {
        out.print("irest={},", 0);
    }
    out.print("ig=-1,");
    out.print("\n");
    out.print("ntwx={},", nTwx_);
    out.print("ntwv={},", -1);
    out.print("ioutfm={},", iOutfm_);
    out.print("ntxo={},", nTxo_);
    out.print("ntpr={},", nTpr_);
    out.print("ntwr={},", nTwr_);
    out.print("\n");
    out.print("iwrap={},", 0);
    out.print("nscm={},", nscm_);
    out.print("cut={},", cut_);
    out.print("\n");
    out.print("ntc={},", ntc_);
    out.print("ntf={},", ntf_);
    out.print("ntb={},", ntb_);
    out.print("\n");
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
Md *Md::setRestraintMask(std::string restraintMask)
{
    restraintMask_ = std::move(restraintMask);
    return this;
}
void Md::barostat()
{
    if (baroType_ == baro::berendsen)
    {
        fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
        out.print("ntp={},", ntpFlags_);
        out.print("taup={},", taup_);
        out.print("pres0={},", 1.0);
        out.print("\n");
    } else if (baroType_ == baro::montecarlo)
    {
        fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
        out.print("ntp={},", ntpFlags_);
        out.print("barostat={},", 2);
        out.print("pres0={},", 1.0);
        out.print("mcbarint={},", mcbarint_);
        out.print("\n");
    } else
    {
        throw std::runtime_error("The thermo must be berendsen of montecarlo");
    }
}
void Md::Thermostat()
{
    if (thermoType_ == thermo::berendsen)
    {
        fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
        out.print("ntt={},", 1);
        out.print("tautp={},", tautp_);
        out.print("temp0={},", temp_);
        out.print("tempi={},", temp_);
        out.print("\n");
    } else if (thermoType_ == thermo::langevin)
    {
        fmt::ostream out = fmt::output_file(name_ + ".in", fmt::file::WRONLY | fmt::file::APPEND);
        out.print("ntt={},", 3);
        out.print("gamma_ln={},", gamma_ln_);
        out.print("temp0={},", temp_);
        out.print("tempi={},", temp_);
        out.print("\n");
    } else
    {
        throw std::runtime_error("The thermo must be berendsen of langevin");
    }
}
Md *Md::setCut(float cut)
{
    cut_ = cut;
    return this;
}
Md *Md::setNTpr(int ntpr)
{
    nTpr_ = ntpr;
    return this;
}
Md *Md::setNTwx(int ntwx)
{
    nTwx_ = ntwx;
    return this;
}
Md *Md::setNTwr(int ntwr)
{
    nTwr_ = ntwr;
    return this;
}
Md *Md::setNstLim(int nstlim)
{
    nstLim_ = nstlim;
    return this;
}
Md *Md::setIrest(bool irest)
{
    if (irest)
    {
        iRest_ = irest;
    } else
    {
        iRest_ = irest;
    }
    return this;
}
Md *Md::setTautp(float tautp)
{
    tautp_ = tautp;
    return this;
}
Md *Md::settaup(float taup)
{
    taup_ = taup;
    return this;
}
Md *Md::setMcbarint(int mcbarint)
{
    mcbarint_ = mcbarint;
    return this;
}
Md *Md::setGammaLn(float gamma_ln)
{
    gamma_ln_ = gamma_ln;
    return this;
}
Md *Md::setDt(float dt)
{
    dt_ = dt;
    return this;
}
Md *Md::setNscm(int nscm)
{
    nscm_ = nscm;
    return this;
}
Md *Md::setNtx(int ntx)
{
    ntx_ = ntx;
    return this;
}
Md *Md::setNtc(int ntc)
{
    ntc_ = ntc;
    return this;
}
Md *Md::setNtf(int ntf)
{
    ntf_ = ntf;
    return this;
}
Md *Md::setNtb(int ntb)
{
    ntb_ = ntb;
    return this;
}
Md *Md::setBarostat(const std::string &baroType)
{
    if (baroType == "berendsen")
    {
        baroType_ = baro::berendsen;
    } else if (baroType == "montecarlo")
    {
        baroType_ = baro::montecarlo;
    } else
    {
        throw std::runtime_error("Baro type must be berendsen or montecarlo");
    }
    return this;
}
Md *Md::setThermostat(const std::string &thermoType)
{
    if (thermoType == "berendsen")
    {
        thermoType_ = thermo::berendsen;
    } else if (thermoType == "langevin")
    {
        thermoType_ = thermo::langevin;
    } else
    {
        throw std::runtime_error("Thermo type must be berendsen or langevin");
    }
    return this;
}
Md *Md::setTemp(float temp)
{
    temp_ = temp;
    return this;
}
void Md::runMd()
{
    Base::runMd();
}
Md *Md::setRestraint_wt(float restraint_wt)
{
    restraint_wt_ = restraint_wt;
    return this;
}
void Md::progress()
{
    run_.acquire();
    int index = 0;
    tqdm bar;
    bar.set_label(name_);
    fswatcher_t watcher = fswatcher_create(FSWATCHER_CREATE_DEFAULT, FSWATCHER_EVENT_ALL, ".", nullptr);

    while (!this->done_)
    {
        fswatcher_event_handler handler = {[&](fswatcher_event_handler *handler, fswatcher_event_type evtype, const char *src, const char *dst) -> bool {
            if (src == "./" + this->name_ + ".out")
            {
                (void) handler;
                (void) dst;

                switch (evtype)
                {
                    case FSWATCHER_EVENT_CREATE:
                        index += 300;
                        bar.progress(index, this->nstLim_);
                        break;
                    case FSWATCHER_EVENT_MODIFY:
                        index += 300;
                        bar.progress(index, this->nstLim_);
                        break;
                    default:
                        printf("unhandled event!\n");
                }
            }
            return true;
        }};
        fswatcher_poll(watcher, &handler, nullptr);
    };
    bar.finish();
    fswatcher_destroy(watcher);
    pro_.release();
}