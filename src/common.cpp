//
// Created by jack on 2022/9/19.
//
#include <cstring>
#include <filesystem>
#include <vector>
std::vector<std::string> executeCMD(const std::string &strCmd)
{
    char buf[1024] = {0};
    FILE *pf = nullptr;

    if ((pf = popen(strCmd.c_str(), "r")) == nullptr)
    {
        return {};
    }

    std::string strResult;
    while (fgets(buf, sizeof buf, pf))
    {
        strResult += buf;
    }
    pclose(pf);
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