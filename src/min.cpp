//
// Created by jack on 2022/9/21.
//
#include "min.hpp"
Min::Min(std::string name,int nTmin, int maxCyc, int nCyc, int nTwx, int nTpr, int nTwr)
{
    name_ = name;
    nTmin_ = nTmin;
    maxCyc_=maxCyc;
    nCyc_ = nCyc;
    nTwx_=nTwx;
    nTpr_ = nTwr;
    iMin_ = 1;
}