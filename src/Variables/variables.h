#pragma once

#include <unordered_map>
#include <string>
#include <vector>


class VarSys
{
public:
    void Set(const std::string& name, const std::string& value);
    std::string Get(const std::string& name);

private:
    std::unordered_map<std::string, std::string> vars;
};


