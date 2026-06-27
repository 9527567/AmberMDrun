#ifndef AMBERMD_COMMON_HPP
#define AMBERMD_COMMON_HPP
#include <string>
#include <vector>
#include "fswatch.hpp"

/// @brief Check if a value exists in a vector.
/// @tparam T Any equality-comparable type
/// @param t  Value to search for
/// @param vec Vector to search in
/// @return true if t is found in vec
template<typename T>
bool isIn(T t, std::vector<T> vec)
{
    for (const auto &i: vec)
    {
        if (t == i) return true;
    }
    return false;
}

/// @brief Execute a shell command and capture stdout line-by-line.
/// @param strCmd Shell command string
/// @return Vector of output lines
/// @throws std::runtime_error if popen or pclose fails
std::vector<std::string> executeCMD(const std::string &strCmd);

/// @brief Remove leading and trailing whitespace from a string (in-place).
inline void trim(std::string &s)
{
    if (s.empty())
    {
        return;
    }
    s.erase(0, s.find_first_not_of(' '));
    s.erase(s.find_last_not_of(' ') + 1);
}

/// @brief Execute a command via fork/exec and capture stdout.
/// @param args      Command and arguments as a vector
/// @param inc_stderr Whether to capture stderr into stdout
/// @return Captured stdout string
[[maybe_unused]] std::string executeCMD2(const std::vector<std::string>& args, const bool inc_stderr = false);
#endif//AMBERMD_COMMON_HPP
