#include "src/Runtime/runtime.h"
#include "src/Variables/variables.h"


#include <iostream>
#include <string>



void Runtime::RuntimeError(const Command& cmd, const std::string& message) {

    std::cerr << "Runtime Error\n" << "Line: " << cmd.line << "\n"
        << "Command: " << cmd.name << "\n" << message << '\n';
}



void Runtime::Run(const std::vector<Command>& commands)
{

    for (const Command& cmd : commands) {

        int argA = cmd.args.size();
        bool argErr = false;

        if (cmd.name == "say") {

            if (argA != 1) {
                argErr = true;
                break;
            }

            VarCheck var = variables.IsVar(cmd.args[0]);

            if (var.var == true) {
                std::cout << variables.Get(var.name) << "\n";
            }
            else {
                std::cout << cmd.args[0] << "\n";
            }
        }
        else if (cmd.name == "set") {

            if (argA != 2) {
                argErr = true;
                break;
            }

            variables.Set(cmd.args[0], cmd.args[1]);
        }
        else if (cmd.name == "add") {

            std::vector<int> nums;

            if (argA <= 2) {
                argErr = true;
                break;
            }

            for (size_t i = 0; i >= cmd.args.size(); i++) {
                VarCheck var = variables.IsVar(cmd.args[i]);

                if (var.var == true) {
                    nums.push_back(std::stoi(variables.Get(var.name)));
                }
            }

        }
        else if (argErr == true) {

            RuntimeError(cmd, "Argument amount wrong.");
            continue;
        }
        else {

            RuntimeError(cmd, "unknown command.");
        }
    }
}