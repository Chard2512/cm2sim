#include <iostream>
#include <iomanip>
#include <chrono>
#include "parser.hpp"
#include "strutils.hpp"
#define VERSION "0.1"

double simulationTickrate = 20;

std::string progName;

void usage() {
    std::cout << "Usage: " << progName << " [OPTION]... [FILE]\n";
    std::cout << "Run a simulation of a Circuit Maker 2 module in a 2D graphical environment.\n\n";
    std::cout << "Example: " << progName << " -fv savestring.txt\n\n";
    std::cout << "Arguments:\n";
    std::cout << std::left
              << std::setw(30) << "  -c, --cli"
              << "Run without graphical interface.\n"
              << std::setw(30) << "  -f"
              << "Reads a savestring file to simulate.\n"
              << std::setw(30) << "  -h, --help"
              << "Prints this help message.\n"
              << std::setw(30) << "  -v, --verbose"
              << "Enable verbosity.\n"
              << std::setw(30) << "  -t, --tickrate=RATE"
              << "Set simulation tickrate (default: 20).\n"
              << std::setw(30) << "  --version"
              << "Prints program's version." << std::endl;
}

void runSimulation(Module module, bool verbosity, bool cliOnly) {
    using namespace std::chrono;

    auto simulationStepTime = microseconds(static_cast<int64_t>(1000000 / simulationTickrate));
    auto buffer = high_resolution_clock::now();

    while (true) {  
        auto diff = high_resolution_clock::now() - buffer;
        while (diff >= simulationStepTime) {
            buffer += simulationStepTime;

            module.update();
        }
    }
}

int main(int argc, char* argv[]) {
    progName = argv[0];
 
    if (argc == 1) {
        usage();
        return 0;
    }

    bool execFile;
    std::string filePath;
    bool verbosity;
    bool cliOnly;

    for (int i = 0; i < argc; i++) {
        const std::string arg = argv[i];

        if (arg[0] == '-') {
            if (arg[1] == '-') {
                std::string op = arg.substr(2);
                if (op == "cli") {
                    cliOnly = true;
                } else
                if (op == "help") {
                    usage();
                    return 0;
                } else
                if (op == "verbose") {
                    verbosity = true;
                } else
                if (op == "version") {
                    std::cout << "cm2sim " << VERSION << std::endl;
                    return 0;
                } else
                if (startsWith(op, "tickrate=")) {
                    simulationTickrate = std::stod(substrFromChar(op, '='));
                } else {
                    std::cerr << "Unrecognized option '" << op << "'." << std::endl;
                }
            } else {
                std::string ops = arg.substr(1);
                for (auto op : ops) {
                    if (op == 'c') {
                        cliOnly = true;
                    } else
                    if (op == 'h') {
                        usage();
                        return 0;
                    } else
                    if (op == 'f') {
                        execFile = true;
                        if (i + 1 >= argc) {
                            std::cerr << "What you want me to read? :<" << std::endl;
                            return 1;
                        }
                        filePath = argv[i + 1];
                    } else
                    if (op == 'v') {
                        verbosity = true;
                    } else 
                    if (op == 't') {
                        if (i + 1 >= argc) {
                            std::cerr << "I require a tickrate definition! :<" << std::endl;
                            return 1;
                        }
                        simulationTickrate = std::stod(argv[i + 1]);
                    } else {
                        std::cerr << "Unrecognized option '" << op << "'." << std::endl;
                        return 1;
                    }
                }
            }
        }
    }

    if (execFile) {
        Module module = Module();
        if (!loadModule(module, filePath)) {
            return 1;
        }
        runSimulation(module, verbosity, cliOnly);
        return 0;
    } else {
        usage();
        return 1;
    }
}