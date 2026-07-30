#include "src/Runtime/runtime.h"
#include "src/Variables/variables.h"


#include <iostream>
#include <string>
#include <stdexcept>


void Runtime::Say(const Command& cmd) {

    VarCheck var = variables.IsVar(cmd.args[0]);

    if (var.var == true) {

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

    std::vector<int> nums;
    int addNums = 0;
    int fAddNums = 0;

    for (size_t i = 1; i < cmd.args.size(); i++) {

        VarCheck var = variables.IsVar(cmd.args[i]);

        std::string varAmt = variables.Get(var.name);

        try {

            if (var.var == true) {
                nums.push_back(std::stoi(varAmt));
            }
            else {
                nums.push_back(std::stoi(cmd.args[i]));
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

    std::string varAmt = variables.Get(var.name);

    variables.Set(var.name, std::to_string(addNums + std::stoi(varAmt)));
}