#include "parser.h"
#include "runtime.h"

#include <iostream>


int main() {

    ErrMes err;
    auto commands = ParseFile("Story Items/Test.uvnn", err);

    if (!err.Err.empty()) {
        std::cout << "\nParse error at line " << err.line << ": " << err.Err << "\n";
        return 1;
    }

    Runtime runtime;

    runtime.Run(commands);
}