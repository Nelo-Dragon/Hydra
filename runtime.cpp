#include "runtime.h"

#include <iostream>


void Runtime::Run(const std::vector<Command>& commands)
{

    for (const Command& cmd : commands){

        if (cmd.name == "say") {
            
            std::cout << cmd.args[0] << "\n";
        }
    }
}