#pragma once

#include "parser.h"


class Runtime
{
public:
    void Run(const std::vector<Command>& commands);

private:
    std::string cBack;
    std::string cMusic;
};
