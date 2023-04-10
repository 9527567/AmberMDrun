//
// Created by jack on 2022/9/21.
//
#include "min.hpp"

#include "fmt/core.h"
#include "fmt/os.h"
#include <utility>
Min::Min(const std::string &name, SystemInfo systemInfo, const std::string &rst7, const std::string &refc, bool irest, const std::string &restrintmask, float restrant_wt, float cut, int nTmin, int maxCyc, int nCyc, int nTwx, int nTpr, int nTwr)
{
    name_ = name;
    systemInfo_ = std::move(systemInfo);
    rst7_ = rst7;
    refc_ = refc;
    iRest_ = irest;
    restraintMask_ = restrintmask;
    restraint_wt_ = restrant_wt;
    cut_ = cut;
    nTmin_ = nTmin;
    maxCyc_ = maxCyc;
    nCyc_ = nCyc;
    nTwx_ = nTwx;
    nTpr_ = nTwr;
    nTwr_ = nTwr;
    iMin_ = 1;
}
void Min::operator()(std::string name, int nTmin, int maxCyc, int nCyc, int nTwx, int nTpr, int nTwr)
{
    name_ = name;
    nTmin_ = nTmin;
    maxCyc_ = maxCyc;
    nCyc_ = nCyc;
    nTwx_ = nTwx;
    nTpr_ = nTwr;
    iMin_ = 1;
}
void Min::writeInput()
{
    fmt::ostream out = fmt::output_file(name_ + ".in");
    out.print("Minimization:{}\n", name_);
    out.print("&cntrl\n");
    out.print("imin={},", iMin_);
    out.print("ntmin={},", nTmin_);
    out.print("maxcyc={},", maxCyc_);
    out.print("ncyc={},", nCyc_);
    out.print("\n");
    out.print("ntwx={},", nTwx_);
    out.print("ioutfm={},", iOutfm_);
    out.print("ntxo={},", nTxo_);
    out.print("ntpr={},", nTpr_);
    out.print("ntwr={},", nTwr_);
    out.print("\n");
    out.print("ntc={},", ntc_);
    out.print("ntf={},", ntf_);
    out.print("ntb={},", ntb_);
    out.print("cut={:.1f},", cut_);
    out.print("\n");
}
void Min::charmmWater()
{
    Base::charmmWater();
}
void Min::restraint()
{
    Base::restraint();
}
void Min::writeEnd()
{
    Base::writeEnd();
}
void Min::Run()
{
    Base::Run();
}
Min *Min::setRestraintMask(std::string restraintMask)
{
    restraintMask_ = std::move(restraintMask);
    return this;
}
Min *Min::setCut(float cut)
{
    cut_ = cut;
    return this;
}
Min *Min::setMaxCyc(int maxcyc)
{
    maxCyc_ = maxcyc;
    return this;
}
Min *Min::setNCyc(int cyc)
{
    nCyc_ = cyc;
    return this;
}
Min *Min::setNTim(int ntmin)
{
    nTmin_ = ntmin;
    return this;
}
Min *Min::setNTpr(int ntpr)
{
    nTpr_ = ntpr;
    return this;
}
Min *Min::setNTwr(int ntwr)
{
    nTwr_ = ntwr;
    return this;
}
Min *Min::setNTwx(int ntwx)
{
    nTwx_ = ntwx;
    return this;
}
void Min::runMd()
{
    Base::runMd();
}
Min *Min::setRestraint_wt(float restraint_wt)
{
    restraint_wt_ = restraint_wt;
    return this;
}
void Min::progress()
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
                        index += this->nTpr_;
                        bar.progress(index, this->maxCyc_);
                        break;
                    case FSWATCHER_EVENT_MODIFY:
                        index += this->nTpr_;
                        bar.progress(index, this->maxCyc_);
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
