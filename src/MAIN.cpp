#include "src/Parser/parser.h"
#include "src/Runtime/runtime.h"

#include <iostream>
#include <chrono>


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

    auto start = std::chrono::steady_clock::now();

    runtime.Run(commands);

    auto end = std::chrono::steady_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;

    if (argc >= 3 && std::string(argv[2]) == "--time") {

        std::cout << "\nRuntime:" << elapsed.count() << " ms\n";
    }
}