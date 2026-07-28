#include <iostream>

#include "parser.h"



int main() {

    auto commands = ParseFile("Story Items/Test.uvnn");

    for (const Command& cmd : commands) {
        
        std::cout << cmd.line << ". " << "Command: " << cmd.name << "\n";

        for (const std::string& arg : cmd.args) {

            std::cout << "Arguments: " << arg << "\n";
        }
    }
}