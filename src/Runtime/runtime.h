#pragma once

#include "src/Parser/parser.h"
#include "src/Variables/variables.h"


class Runtime
{
public:

    void Run(const std::vector<Command>& commands);


private:

    void RuntimeError(const Command& cmd, const std::string& message);

    void Say(const Command& cmd);
    void Set(const Command& cmd);
    void Add(const Command& cmd);

    VarSys variables;

    std::string cBack;
    std::string cMusic;
};