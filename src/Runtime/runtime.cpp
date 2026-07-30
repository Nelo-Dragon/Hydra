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

    std::string argErr = "Argument amount wrong.";

    for (const Command& cmd : commands) {

        int argA = cmd.args.size();

        if (cmd.name == "say") {

            if (argA != 1) {

                RuntimeError(cmd, argErr);
                continue;
            }

            Say(cmd);
        }
        else if (cmd.name == "set") {

            if (argA != 2) {

            RuntimeError(cmd, argErr);
            continue;
            }

            Set(cmd);
        }
        else if (cmd.name == "add") {

            if (argA < 2) {

                RuntimeError(cmd, argErr);
                continue;
            }

            Add(cmd);
        }
        else if (cmd.name == "sub") {

            if (argA < 2) {

                RuntimeError(cmd, argErr);
                continue;
            }

            Sub(cmd);
        }
        else if (cmd.name == "mlt") {

            if (argA < 2) {

                RuntimeError(cmd, argErr);
            }

            Mlt(cmd);
        }
        else if (cmd.name == "div") {

            if (argA < 2) {

                RuntimeError(cmd, argErr);
            }

            Div(cmd);
        }
        else {

            RuntimeError(cmd, "unknown command.");
        }
    }
}