//
// Created by jack on 2022/9/19.
//

#ifndef AMBERMD_BASE_HPP
#define AMBERMD_BASE_HPP
#include <string>
class Base
{
public:
    Base(float cut = 8.0);
    ~Base() = default;
    virtual void createInput();

protected:
    std::string name_;
    int iMin_;
    float cut_;
    std::string restraintMask;
    int nTwx_;
    int nTwr_;
    int nTpr_;
};
#endif//AMBERMD_BASE_HPP
