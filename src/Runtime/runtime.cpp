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

    float a;
    float b;

    try {

        a = std::stof(left);
        b = std::stof(right);
    }
    catch (const std::invalid_argument) {

        return false;
    }
    
    if (op == "=") {

        return a == b;
    }
    else if (op == "!=") {

        return a != b;
    }
    else if (op == "<") {

        return a < b;
    }
    else if (op == ">") {

        return a > b;
    }
    else if (op == "<=") {

        return a <= b;
    }
    else if (op == ">=") {

        return a >= b;
    }
    else {

        return false;
    }
}


void Runtime::Run(const std::vector<Command>& commands)
{

    std::string argErr = "Argument amount wrong.";

    IsIf isIf;
    IsLoop isLoop;

    for (size_t i = 0; i < commands.size(); i++) {

        Command cmd = commands[i];
        
        int argA = cmd.args.size();

        if (cmd.name == "if") {

            if (argA != 3) {

                RuntimeError(cmd, argErr);
                continue;
            }

            isIf = If(cmd, isIf);
            continue;
        }

        if (cmd.name == "elseIf" || cmd.name == "elif") {

            if (argA !=3) {

                RuntimeError(cmd, argErr);
                continue;
            }

            isIf = ElseIf(cmd, isIf);
            continue;
        }

        if (cmd.name == "else") {

            if (argA != 0) {

                RuntimeError(cmd, argErr);
                continue;
            }

            isIf = Else(cmd, isIf);
            continue;
        }

        if (cmd.name == "loop") {

            if (argA != 1) {

                RuntimeError(cmd, argErr);
                continue;
            }

            isLoop = Loop(cmd, isLoop);
            continue;
        }

        if (cmd.name == "end") {
            
            if (argA != 0) {

                RuntimeError(cmd, argErr);
                continue;
            }

            bool hasIf = !isIf.lineN.empty();
            bool hasLoop = !isLoop.lineN.empty();

            if (!hasIf && !hasLoop) {

                RuntimeError(cmd, "Unexpected end.");
                continue;
            }

            if (hasIf && hasLoop) {

                if (isIf.lineN.back() > isLoop.lineN.back()) {

                    isIf = EndIf(cmd, isIf);
                }
                else {

                    isLoop = EndLoop(cmd, isLoop);
                    i = isLoop.lineN.back() - 1;
                }
            }
            else if (hasIf) {

                isIf = EndIf(cmd, isIf);
            }
            else {

                isLoop = EndLoop(cmd, isLoop);

                if (!isLoop.lineN.empty()) {

                    i = isLoop.lineN.back() - 1;
                }
            }

            continue;
        }

        if (!isIf.ifBad.empty()) {

            bool shouldSkip = false;

            for (bool bad : isIf.ifBad) {

                if (bad) {

                    shouldSkip = true;
                    break;
                }
            }

            if (shouldSkip) {

            continue;
            }
        }

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
        else if (cmd.name == "kill") {

            if (argA == 0) {

                RuntimeError(cmd, argErr);
                continue;
            }

            Kll(cmd);
        }
        else if (cmd.name == "ask") {

            if (argA != 2) {

                RuntimeError(cmd,argErr);
                continue;
            }

            Ask(cmd);
        }
        else if (cmd.name == "add") {

            if (argA < 2) {

                RuntimeError(cmd, argErr);
                continue;
            }

            Add(cmd);
        }
        else if (cmd.name == "sub" || cmd.name == "subtract") {

            if (argA < 2) {

                RuntimeError(cmd, argErr);
                continue;
            }

            Sub(cmd);
        }
        else if (cmd.name == "mult" || cmd.name == "multiply") {

            if (argA < 2) {

                RuntimeError(cmd, argErr);
                continue;
            }

            Mlt(cmd);
        }
        else if (cmd.name == "div" || cmd.name == "divide") {

            if (argA < 2) {

                RuntimeError(cmd, argErr);
                continue;
            }

            Div(cmd);
        }
        else {

            RuntimeError(cmd, "unknown command.");
        }
    }
}