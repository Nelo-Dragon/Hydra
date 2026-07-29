#include "src/Runtime/runtime.h"


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

            if (cmd.args[0][0] == '$') {
                std::string varName = cmd.args[0];
                varName.erase(0, 1);
                std::cout << variables.Get(varName) << "\n";
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
        else if (argErr == true) {

            RuntimeError(cmd, "Argument amount wrong.");
            continue;
        }
        else {

            RuntimeError(cmd, "unknown command.");
        }
    }
}