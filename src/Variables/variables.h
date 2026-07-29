#pragma once

#include <unordered_map>
#include <string>
#include <vector>
struct VarCheck {
    
    bool var;
    std::string name;
};

class VarSys
{
public:

    void Set(const std::string& name, const std::string& value);
    std::string Get(const std::string& name);

    VarCheck IsVar(const std::string& arg);

private:
    std::unordered_map<std::string, std::string> vars;

};


