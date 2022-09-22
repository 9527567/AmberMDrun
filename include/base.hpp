//
// Created by jack on 2022/9/19.
//

#ifndef AMBERMD_BASE_HPP
#define AMBERMD_BASE_HPP
#include <string>
class Base
{
public:
    explicit Base(std::string name, float cut = 8.0);
    Base() = default;
    ~Base() = default;
    virtual void operator()(float cut = 8.0);
protected:
    virtual void writeInput();
    std::string name_;
    int iMin_{};
    float cut_{8.0};
    std::string restraintMask;
    int nTwx_{};
    int nTwr_{};
    int nTpr_{};
};
#endif//AMBERMD_BASE_HPP
