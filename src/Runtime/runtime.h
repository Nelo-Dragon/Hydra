#pragma once

#include "src/Parser/parser.h"
#include "src/Variables/variables.h"


class Runtime
{
public:

    void Run(const std::vector<Command>& commands);


private:

    struct IsIf 
    {

        std::vector<bool> ifBad;
    };

    struct IsLoop
    {

        std::vector<bool> isOut;
        std::vector<int> loopN;
        std::vector<int> iteration;
    };

    void RuntimeError(const Command& cmd, const std::string& message);

    void Say(const Command& cmd);
    void Set(const Command& cmd);
    void Kll(const Command& cmd);
    void Add(const Command& cmd);
    void Sub(const Command& cmd);
    void Mlt(const Command& cmd);
    void Div(const Command& cmd);
    void Ask(const Command& cmd);

    IsIf If(const Command& cmd, const IsIf& inIf);
    IsIf ElseIf(const Command& cmd, const IsIf& inIf);
    IsIf Else(const Command& cmd, const IsIf& inIf);
    IsIf EndIf(const Command& cmd, const IsIf& inIf);

    bool Compare(const std::string& left, const std::string& op, const std::string& right);

    std::string FtoS(float input);

    VarSys variables;

    std::string cBack;
    std::string cMusic;
};