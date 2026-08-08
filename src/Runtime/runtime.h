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
        std::vector<bool> branchTaken;
        std::vector<int> lineN;
    };

    struct IsLoop
    {

        std::vector<int> lineN;
        std::vector<int> iteration;
    };
    
    struct IsFor
    {
        
        std::vector<int> lineN;
        std::vector<int> iteration;
        std::vector<const Command> cmd;
        std::vector<bool> forBad;
    };

    void RuntimeError(const Command& cmd, const std::string& message);

    void Say(const Command& cmd);
    void Set(const Command& cmd);
    void Kll(const Command& cmd);
    void Rnd(const Command& cmd);
    void Add(const Command& cmd);
    void Sub(const Command& cmd);
    void Mlt(const Command& cmd);
    void Div(const Command& cmd);
    void Ask(const Command& cmd);

    IsLoop Loop(const Command& cmd, const IsLoop& isLoop, const size_t& commandIndex);
    IsLoop EndLoop(const Command& cmd, const IsLoop& isLoop);
    IsFor For(const Command& cmd, const IsFor& isFor, const size_t& commandIndex);
    IsFor EndFor(const Command& cmd, const IsFor& IsFor);
    

    IsIf If(const Command& cmd, const IsIf& inIf, const size_t& commandIndex);
    IsIf ElseIf(const Command& cmd, const IsIf& inIf);
    IsIf Else(const Command& cmd, const IsIf& inIf);
    IsIf EndIf(const Command& cmd, const IsIf& inIf);
  
    std::vector<std::string> Comparitors(const Command& cmd);
    bool Compare(const std::string& left, const std::string& op, const std::string& right);

    std::string FtoS(float input);

    std::vector<float> ParseNums(const Command& cmd);
    float ParseNum(const Command& cmd, const std::string& input);

    VarSys variables;

    std::string cBack;
    std::string cMusic;
};