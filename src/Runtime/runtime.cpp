#include "src/Runtime/runtime.h"
#include "src/Variables/variables.h"

#include <iostream>
#include <string>
#include <stdexcept>



void Runtime::RuntimeError(const Command& cmd, const std::string& message) {

    std::cerr << "Runtime Error\n" << "Line: " << cmd.line << "\n"
        << "Command: " << cmd.name << "\n" << message << '\n';
}

bool Runtime::Compare(const std::string& left, const std::string& op, const std::string& right) {
    
    if (op == "=") {

        return left == right;
    }
    else if (op == "!=") {

        return left != right;
    }
    else if (op == "<") {

        return left < right;
    }
    else if (op == ">") {

        return left > right;
    }
    else if (op == "<=") {

        return left <= right;
    }
    else if (op == ">=") {

        return left >= right;
    }
    else {

        return false;
    }
}


void Runtime::Run(const std::vector<Command>& commands)
{

    std::string argErr = "Argument amount wrong.";

    IsIf isIf;

    for (const Command& cmd : commands) {

        
        int argA = cmd.args.size();

        if (cmd.name == "if") {

            if (argA < 2) {

                RuntimeError(cmd, argErr);
            }

            isIf = If(cmd, isIf);
        }
        else if (!isIf.inIf == 0) {

            if (isIf.ifBad[isIf.inIf] == true) {

            continue;
            }
        }
        else if (cmd.name == "say") {

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
        else if (cmd.name == "kill") {

            if (argA == 0) {

                RuntimeError(cmd, argErr);
                continue;
            }

            Kll(cmd);
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