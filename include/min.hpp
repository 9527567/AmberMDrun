//
// Created by jack on 2022/9/21.
//

#ifndef AMBERMD_MIN_HPP
#define AMBERMD_MIN_HPP
#include "base.hpp"
class Min : Base
{
public:
    explicit Min(std::string name,int nTmin = 2, int maxCyc = 1000, int nCyc = 10, int nTwx = 500, int nTpr = 50, int nTwr = 500);
    ~Min() = default;
    void operator()(std::string name,int nTmin = 2, int maxCyc = 1000, int nCyc = 10, int nTwx = 500, int nTpr = 50, int nTwr = 500);
protected:
    void writeInput() override;
    int nTmin_;
    int maxCyc_;
    int nCyc_;
    int cut_;
    const int iOutfm_ = 1;
    const int nTxo_ = 2;
    const int ntc_ = 1;
    const int ntf_ = 1;
    const int ntb_ = 1;
};
#endif//AMBERMD_MIN_HPP
