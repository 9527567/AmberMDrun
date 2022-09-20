//
// Created by jack on 2022/9/19.
//

#ifndef AMBERMD_BASE_HPP
#define AMBERMD_BASE_HPP
class Base
{
public:
    Base(int iMin = 1);
    ~Base() = default;
    virtual void createInput();

private:
    int iMin_;

};
#endif//AMBERMD_BASE_HPP
