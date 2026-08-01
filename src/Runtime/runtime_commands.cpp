#include "src/Runtime/runtime.h"
#include "src/Variables/variables.h"


#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>

std::string Runtime::FtoS(float input) {

    std::ostringstream stream;
    stream << input;
    return stream.str();
}

void Runtime::Say(const Command& cmd) {

    VarCheck var = variables.IsVar(cmd.args[0]);

    if (var.var) {

        std::cout << variables.Get(var.name) << "\n";
    }
    else {

        std::cout << cmd.args[0] << "\n";
    }
}

void Runtime::Set(const Command& cmd) {

    variables.Set(cmd.args[0], cmd.args[1]);
}

void Runtime::Add(const Command& cmd) {

    std::vector<float> nums;
    float addNums = 0;

    for (size_t i = 1; i < cmd.args.size(); i++) {

        VarCheck var = variables.IsVar(cmd.args[i]);

        std::string varAmt = variables.Get(var.name);

        try {

            if (var.var) {
                nums.push_back(std::stof(varAmt));
            }
            else {
                nums.push_back(std::stof(cmd.args[i]));
            }
        }
        catch (const std::invalid_argument&) {

            RuntimeError(cmd, "Expexts a number.");
            break;
        }
        catch (const std::out_of_range&) {

            RuntimeError(cmd, "Number is too large.");
                break;
        }
        
    }

    for (size_t i = 0; i < nums.size(); i++) {

        addNums = addNums + nums[i];
    }

    VarCheck var = variables.IsVar(cmd.args[0]);

    if (!var.var) {

        RuntimeError(cmd, "first argument must be a variable.");
        return;
    }

    std::string varAmt = variables.Get(var.name);

    variables.Set(var.name, FtoS(addNums + std::stof(varAmt)));
}

void Runtime::Sub(const Command& cmd) {

    std::vector<float> nums;
    float subNums = 0;

    for (size_t i = 1; i < cmd.args.size(); i++) {

        VarCheck var = variables.IsVar(cmd.args[i]);

        std::string varAmt = variables.Get(var.name);

        try {

            if (var.var) {
                nums.push_back(std::stof(varAmt));
            }
            else {
                nums.push_back(std::stof(cmd.args[i]));
            }
        }
        catch (const std::invalid_argument&) {

            RuntimeError(cmd, "Expexts a number.");
            break;
        }
        catch (const std::out_of_range&) {

            RuntimeError(cmd, "Number is too large.");
                break;
        }
        
    }

    for (size_t i = 0; i < nums.size(); i++) {

        subNums = subNums - nums[i];
    }

    VarCheck var = variables.IsVar(cmd.args[0]);

    if (!var.var) {

        RuntimeError(cmd, "first argument must be a variable.");
        return;
    }

    std::string varAmt = variables.Get(var.name);

    variables.Set(var.name, FtoS(subNums + std::stof(varAmt)));
}

void Runtime::Mlt(const Command& cmd) {

    std::vector<float> nums;
    float mltNums = 1;

    for (size_t i = 1; i < cmd.args.size(); i++) {

        VarCheck var = variables.IsVar(cmd.args[i]);

        std::string varAmt = variables.Get(var.name);

        try {

            if (var.var) {
                nums.push_back(std::stof(varAmt));
            }
            else {
                nums.push_back(std::stof(cmd.args[i]));
            }
        }
        catch (const std::invalid_argument&) {

            RuntimeError(cmd, "Expexts a number.");
            break;
        }
        catch (const std::out_of_range&) {

            RuntimeError(cmd, "Number is too large.");
                break;
        }
        
    }

    for (size_t i = 0; i < nums.size(); i++) {

        mltNums = mltNums * nums[i];
    }

    VarCheck var = variables.IsVar(cmd.args[0]);

    if (!var.var) {

        RuntimeError(cmd, "first argument must be a variable.");
        return;
    }

    std::string varAmt = variables.Get(var.name);

    variables.Set(var.name, FtoS(mltNums * std::stof(varAmt)));
}

void Runtime::Div(const Command& cmd) {

    std::vector<float> nums;

    VarCheck target = variables.IsVar(cmd.args[0]);

    if (!target.var) {

        RuntimeError(cmd, "first argument must be a variable.");
        return;
    }

    float varAmt = std::stof(variables.Get(target.name));

    for (size_t i = 1; i < cmd.args.size(); i++) {

        VarCheck var = variables.IsVar(cmd.args[i]);

        float argDiv;

        if (var.var) {

            argDiv = std::stof(variables.Get(var.name));
        }
        else {
    
            argDiv = std::stof(cmd.args[i]);
        }

        try {

            varAmt = varAmt / argDiv;
        }
        catch (const std::invalid_argument&) {

            RuntimeError(cmd, "Expexts a number.");
            break;
        }
        catch (const std::out_of_range&) {

            RuntimeError(cmd, "Number is too large.");
                break;
        }
        
    }

    variables.Set(target.name, FtoS(varAmt));
}

void Runtime::Ask(const Command& cmd) {

    std::string input;

    std::cout << cmd.args[1];
    std::getline(std::cin, input);

    variables.Set(cmd.args[0], input);

}

void Runtime::Kll(const Command& cmd) {

    for (size_t i = 0; i < cmd.args.size(); i++) {

        variables.Kill(cmd.args[i]);
    }
}

Runtime::IsIf Runtime::If(const Command& cmd, const IsIf& inIf, const size_t& commandIndex) {

    IsIf curIf = inIf;

    VarCheck varA = variables.IsVar(cmd.args[0]);
    VarCheck varB = variables.IsVar(cmd.args[2]);

    std::string a;
    std::string b;

    if (varA.var) {

        a = variables.Get(varA.name);
    }
    else {

        a = cmd.args[0];
    }

    if (varB.var) {

        b = variables.Get(varB.name);
    }
    else {

        b = cmd.args[2];
    }

    curIf.ifBad.push_back(!Compare(a, cmd.args[1], b));
    curIf.branchTaken.push_back(Compare(a, cmd.args[1], b));
    curIf.lineN.push_back(commandIndex);

    return curIf;
}

Runtime::IsIf Runtime::ElseIf(const Command& cmd, const IsIf& inIf) {

    IsIf curIf = inIf;

    if (curIf.ifBad.empty()) {

        RuntimeError(cmd, "Unexpected else.");
        return curIf;
    }

    VarCheck varA = variables.IsVar(cmd.args[0]);
    VarCheck varB = variables.IsVar(cmd.args[2]);

    std::string a;
    std::string b;

    if (varA.var) {

        a = variables.Get(varA.name);
    }
    else {

        a = cmd.args[0];
    }

    if (varB.var) {

        b = variables.Get(varB.name);
    }
    else {

        b = cmd.args[2];
    }

    if (curIf.branchTaken.back()) {

        curIf.ifBad.back() = true;
    }
    else {

        bool result = Compare(a, cmd.args[1], b);

        curIf.ifBad.back() = !result;

        if (result) {

            curIf.branchTaken.back() = true;
        }
    }

    return curIf;
}

Runtime::IsIf Runtime::Else(const Command& cmd, const IsIf& inIf) {

    IsIf curIf = inIf;

    if (curIf.ifBad.empty()) {

        RuntimeError(cmd, "Unexpected else.");
        return curIf;
    }

    if (curIf.branchTaken.back()) {

        curIf.ifBad.back() = true;
    }
    else {

        curIf.ifBad.back() = false;
        curIf.branchTaken.back() = true;
    }

    return curIf;
}

Runtime::IsIf Runtime::EndIf(const Command& cmd, const IsIf& inIf) {

    IsIf curIf = inIf;

    if (curIf.ifBad.empty()) {

        RuntimeError(cmd, "Unexpected endIf.");
        return curIf;
    }

    curIf.ifBad.pop_back();
    curIf.lineN.pop_back();

    return curIf;
}

Runtime::IsLoop Runtime::Loop(const Command& cmd, const IsLoop& isLoop,  const size_t& commandIndex) {

    IsLoop curLoop = isLoop;

    VarCheck var = variables.IsVar(cmd.args[0]);

    int iterations;

    if (!var.var) {

        iterations = std::stoi(cmd.args[0]);
    }
    else {

        iterations = std::stoi(variables.Get(var.name));
    }

    if (iterations <= 0) {

        RuntimeError(cmd, "Iteration number less than 1.");
        return curLoop;
    }

    curLoop.lineN.push_back(commandIndex);
    
    curLoop.iteration.push_back(iterations);

    return curLoop;
}

Runtime::IsLoop Runtime::EndLoop(const Command& cmd, const IsLoop& isLoop) {

    IsLoop curLoop = isLoop;

    if (curLoop.iteration.empty()) {

        RuntimeError(cmd, "Unexpected endloop.");
        return curLoop;
    }

    curLoop.iteration.back() -= 1;

    if (curLoop.iteration.back() <= 0) {

        curLoop.iteration.pop_back();
        curLoop.lineN.pop_back();
    }

    return curLoop;
}