#include "src/Runtime/runtime.h"
#include "src/Variables/variables.h"


#include <iostream>
#include <string>
#include <stdexcept>
#include <sstream>
#include <random>
#include <cmath>

std::string Runtime::FtoS(float input) {

    std::ostringstream stream;
    stream << input;
    return stream.str();
}

std::vector<std::string> Runtime::Comparitors(const Command& cmd) {
  
    std::vector<std::string> output;
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
  
    output.push_back(a);
    output.push_back(b);
  
    return output;
}

float Runtime::ParseNum(const Command& cmd, const std::string& input) {

    VarCheck var = variables.IsVar(input);

    std::string value = input;

    if (var.var) {

        value = variables.Get(var.name);
    }

    try {

        return std::stof(value);
    }
    catch (const std::invalid_argument&) {

        RuntimeError(cmd, "Expects a number.");
        return 0;
    }
    catch (const std::out_of_range&) {

        RuntimeError(cmd, "Number is too large.");
        return 0;
    }
}

std::vector<float> Runtime::ParseNums(const Command& cmd) {

    std::vector<float> curNums;

    for (size_t i = 0; bool debug = i < cmd.args.size(); i++) {

        curNums.push_back(ParseNum(cmd, cmd.args[i]));
    }

    return curNums;
}

void Runtime::Say(const Command& cmd) {

    for (const std::string& arg : cmd.args) {

        VarCheck var = variables.IsVar(arg);

        if (var.var) {

            std::cout << variables.Get(var.name);
        }
        else {

            std::cout << arg;
        }
    }
    std::cout << "\n";
}

void Runtime::Set(const Command& cmd) {

    variables.Set(cmd.args[0], cmd.args[1]);
}

void Runtime::Rnd(const Command& cmd) {
  
    float min = ParseNum(cmd, cmd.args[1]);
    float max = ParseNum(cmd, cmd.args[2]);
  
    std::random_device rd;
  
    std::mt19937 gen(rd());
  
    std::uniform_int_distribution<int> distrib(std::trunc(min), std::trunc(max));
  
  
  
    variables.Set(cmd.args[0], std::to_string(distrib(gen)));
}

void Runtime::Add(const Command& cmd) {

    std::vector<float> nums = ParseNums(cmd);
    float addNums = 0;
   
    int debug;
    
    for (size_t i = 0; i < nums.size(); i++) {
        
        addNums = addNums + nums[i];
    }

    VarCheck var = variables.IsVar(cmd.args[0]);

    if (!var.var) {

        RuntimeError(cmd, "First argument must be a variable.");
        return;
    }
  
    variables.Set(var.name, FtoS(addNums));
}

void Runtime::Sub(const Command& cmd) {

    std::vector<float> nums = ParseNums(cmd);
    float subNums = nums[0];

    for (size_t i = 1; i < nums.size(); i++) {
      
        subNums = subNums - nums[i];
    }

    VarCheck var = variables.IsVar(cmd.args[0]);

    if (!var.var) {

        RuntimeError(cmd, "First argument must be a variable.");
        return;
    }

    variables.Set(var.name, FtoS(subNums));
}

void Runtime::Mlt(const Command& cmd) {

    std::vector<float> nums = ParseNums(cmd);
    float mltNums = 1;

    for (size_t i = 0; i < nums.size(); i++) {

        mltNums = mltNums * nums[i];
    }

    VarCheck var = variables.IsVar(cmd.args[0]);

    if (!var.var) {

        RuntimeError(cmd, "First argument must be a variable.");
        return;
    }

    variables.Set(var.name, FtoS(mltNums));
}

void Runtime::Div(const Command& cmd) {

    std::vector<float> nums = ParseNums(cmd);
    float divNums = nums[0];

    VarCheck var = variables.IsVar(cmd.args[0]);

    if (!var.var) {

        RuntimeError(cmd, "First argument must be a variable.");
        return;
    }

    divNums = ParseNum(cmd, cmd.args[0]);

    for (size_t i = 1; i < nums.size(); i++) {

        if (nums[i] == 0) {

            RuntimeError(cmd, "Can't devide by zero.");
            return;
        }

        divNums = divNums / nums[i];
    }

    variables.Set(var.name, FtoS(divNums));
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
    
    std::vector<std::string> comps = Comparitors(cmd);

    curIf.ifBad.push_back(!Compare(comps[0], cmd.args[1], comps[1]));
    curIf.branchTaken.push_back(Compare(comps[0], cmd.args[1], comps[1]));
    curIf.lineN.push_back(commandIndex);

    return curIf;
}

Runtime::IsIf Runtime::ElseIf(const Command& cmd, const IsIf& inIf) {

    IsIf curIf = inIf;

    if (curIf.ifBad.empty()) {

        RuntimeError(cmd, "Unexpected elseif.");
        return curIf;
    }

    std::vector<std::string> comp = Comparitors(cmd);

    if (curIf.branchTaken.back()) {

        curIf.ifBad.back() = true;
    }
    else {

        bool result = Compare(comp[0], cmd.args[1], comp[1]);

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

Runtime::IsLoop Runtime::EndLoop(const Command& cmd, const IsLoop&  isLoop) {

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

Runtime::IsFor Runtime::For(const Command& cmd, const IsFor& isFor,   const size_t& commandIndex) {
    
    IsFor curFor = isFor;
    
    std::vector<std::string> comps = Comparitors(cmd);
    
    
    
    if (curFor.lineN != commandIndex) {
        curFor.lineN.push_back(commandIndex);
        curFor.iterations.push_back(0);
        curFor.cmd.push_back(cmd);
    }
}