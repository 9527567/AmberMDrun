//
// Created by jack on 2022/9/20.
//

#ifndef AMBERMD_NOCOPYABLE_HPP
#define AMBERMD_NOCOPYABLE_HPP
class noncopyable
{
public:
    noncopyable(const noncopyable &) = delete;
    void operator=(const noncopyable &) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;
};
#endif//AMBERMD_NOCOPYABLE_HPP
