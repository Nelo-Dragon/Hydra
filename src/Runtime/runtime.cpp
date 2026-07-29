#include "src/Runtime/runtime.h"

#include <iostream>


void Runtime::RuntimeError(const Command& cmd, const std::string& message) {

    std::cerr
        << "Runtime Error\n"
        << "Line: " << cmd.line << "\n"
        << "Command: " << cmd.name << "\n"
        << message << '\n';
}


void Runtime::Run(const std::vector<Command>& commands)
{

    for (const Command& cmd : commands){

        if (cmd.name == "say") {
            
            std::cout << cmd.args[0] << "\n";
        }
        else {
            RuntimeError(cmd, "unknown command.");
        }
    }
}