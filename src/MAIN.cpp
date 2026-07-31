#include "src/Parser/parser.h"
#include "src/Runtime/runtime.h"

#include <iostream>


int main(int argc, char* argv[]) {

    if (argc < 2) {

        std::cerr << "Usage: hydra <file>\n";
        return 1;
    }

    std::string filename = argv[1];

    HydraError err;
    auto commands = ParseFile(filename, err);

    if (!err.Err.empty()) {
        std::cout << "\nParse error at line " << err.line << ": " << err.Err << "\n";
        return 1;
    }

    Runtime runtime;

    runtime.Run(commands);
}