#include <iostream>

#include "parser.h"



int main() {

    ErrMes err;
    auto commands = ParseFile("Story Items/Test.uvnn", err);

    for (const Command& cmd : commands) {
        
        std::cout << cmd.line << ". " << "Command: " << cmd.name << "\n";

        for (const std::string& arg : cmd.args) {

            std::cout << "Arguments: " << arg << "\n";
        }
    }

    if (!err.Err.empty()) {
        std::cout << "\nParse error at line " << err.line << ": " << err.Err << "\n";
    }
}