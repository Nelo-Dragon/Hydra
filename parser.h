#pragma once

#include <string>
#include <vector>


struct Command
{
    std::string name;
    std::vector<std::string> args;
    int line = 0;
};

struct ErrMes
{
    std::string token;
    std::string Err;
    int line;
};

std::vector<Command> ParseFile(const std::string& filename);