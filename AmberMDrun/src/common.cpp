//
// Created by jack on 2022/9/19.
//
#include <cstring>
#include <filesystem>
#include <vector>
#include "fmt/format.h"
#include <optional>
std::vector<std::string> executeCMD(const std::string &strCmd)
{
    char buf[1024] = {0};
    FILE *pf = nullptr;

    if ((pf = popen(strCmd.c_str(), "r")) == nullptr)
    {
        throw std::runtime_error(fmt::format("{} run failed!\n",strCmd));
    }

    std::string strResult;
    while (fgets(buf, sizeof buf, pf))
    {
        strResult += buf;
    }
    if(pclose(pf)!=0)
    {
        throw std::runtime_error(fmt::format("{} run failed!\n",strCmd));
    }
    std::vector<std::string> result;
    std::string temp;
    for (auto i: strResult)
    {
        temp.push_back(i);
        if (i == '\n')
        {
            result.emplace_back(temp);
            temp.clear();
        }
    }
    return result;
}
