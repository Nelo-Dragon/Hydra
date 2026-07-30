#include "src/Runtime/runtime.h"
#include "src/Variables/variables.h"


#include <iostream>
#include <string>
#include <stdexcept>



void Runtime::RuntimeError(const Command& cmd, const std::string& message) {

    std::cerr << "Runtime Error\n" << "Line: " << cmd.line << "\n"
        << "Command: " << cmd.name << "\n" << message << '\n';
}



void Runtime::Run(const std::vector<Command>& commands)
{

    for (const Command& cmd : commands) {

        int argA = cmd.args.size();

        if (cmd.name == "say") {

            if (argA != 1) {

            RuntimeError(cmd, "Argument amount wrong.");
            continue;
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

            RuntimeError(cmd, "Argument amount wrong.");
            continue;
            }

            variables.Set(cmd.args[0], cmd.args[1]);
        }
        else if (cmd.name == "add") {

            std::vector<int> nums;
            int addNums = 0;
            int fAddNums = 0;

            if (argA < 2) {

                RuntimeError(cmd, "Argument amount wrong.");
                continue;
            }


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
        else {

            RuntimeError(cmd, "unknown command.");
        }
    }
}