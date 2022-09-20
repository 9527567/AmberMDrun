//
// Created by jack on 2022/9/19.
//

#ifndef AMBERMD_COMMON_HPP
#define AMBERMD_COMMON_HPP

#include <string>
#include <vector>
template<typename T>
bool isIn(T t,std::vector<T> vec)
{
    for (const auto &i:vec)
    {
        if (t==i) return true;
    }
    return false;
}
std::vector<std::string> executeCMD(const std::string &strCmd);

inline void trim(std::string &s)
{
    if (s.empty())
    {
        return ;
    }
    s.erase(0,s.find_first_not_of(' '));
    s.erase(s.find_last_not_of(' ') + 1);
}
#endif //AMBERMD_COMMON_HPP
