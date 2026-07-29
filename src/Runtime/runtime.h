#pragma once

#include "src/Parser/parser.h"


class Runtime
{
public:
    void Run(const std::vector<Command>& commands);

private:
    void RuntimeError(const Command& cmd, const std::string& message);
    std::string cBack;
    std::string cMusic;
};
