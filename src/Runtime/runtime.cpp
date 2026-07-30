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

            Say(cmd);
        }
        else if (cmd.name == "set") {

            if (argA != 2) {

            RuntimeError(cmd, "Argument amount wrong.");
            continue;
            }

            Set(cmd);
        }
        else if (cmd.name == "add") {

            if (argA < 2) {

                RuntimeError(cmd, "Argument amount wrong.");
                continue;
            }

            Add(cmd);
        }
        else {

            RuntimeError(cmd, "unknown command.");
        }
    }
}