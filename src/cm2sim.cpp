#include <iostream>
#include <iomanip>
#include "parser.hpp"
#define VERSION "0.1"

std::string progName;

void usage() {
    std::cout << "Usage: " << progName << " [OPTION] [FILE]\n";
    std::cout << "Simulates a Circuit Maker 2 module in a 2D graphical environment.\n\n";
    std::cout << "Arguments:\n";
    std::cout << std::left
              << std::setw(20) << "  -h, --help"
              << "Prints this help message\n"
              << std::setw(20) << "  -v, --version"
              << "Prints program's version\n"
              << std::setw(20) << "  -f"
              << "Reads a savestring file to simulate\n";
}

int main(int argc, char* argv[]) {
    progName = argv[0];
 
    if (argc == 1) {
        usage();
        return 0;
    }

    for (int i = 0; i < argc; i++) {
        const std::string arg = argv[i];

        if (arg[0] == '-') {
            std::string op;
            if (arg[1] == '-') {
                op = arg.substr(2);
            } else {
                op = arg.substr(1, 1);
            }

            if (op == "help" || op == "h") {
                usage();
                return 0;
            } else
            if (op == "version" || op == "v") {
                std::cout << "cm2sim " << VERSION << std::endl;
                return 0;
            } else
            if (op == "f") {
                return 0;
            }
        }
    }
}