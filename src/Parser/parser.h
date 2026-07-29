#pragma once

#include <string>
#include <vector>


struct Command
{
    std::string name;
    std::vector<std::string> args;
    int line = 0;
};

struct HydraError
{
    std::string token;
    std::string Err;
    int line = 0;
};

std::vector<Command> ParseFile(const std::string& filename, HydraError& outErr);