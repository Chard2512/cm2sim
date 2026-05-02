#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include "strutils.hpp"
#include "parser.hpp"
#include "cliview.hpp"
#define VERSION "0.1"

double simulationTickrate = 20;
double FPS = 30;

std::string progName;

void usage() {
    std::cout << "Usage: " << progName << " [OPTION]... [FILE]\n";
    std::cout << "Run a simulation of a Circuit Maker 2 module in a 2D graphical environment.\n\n";
    std::cout << "Example: " << progName << " -cd savestring.txt \n\n";
    std::cout << "Arguments:\n";
    std::cout << std::left
              << std::setw(30) << "  -c, --cli"
              << "Run on CLI mode (no graphical interface).\n"
              << std::setw(30) << "  -d, --debug"
              << "Enable debug.\n"
              << std::setw(30) << "  -f, --fast"
              << "Run simulation at tickrate limit.\n"
              << std::setw(30) << "  -p, --fps=RATE"
              << "Set simulation framerate (default: 30).\n"
              << std::setw(30) << "  -h, --help"
              << "Prints this help message.\n"
              << std::setw(30) << "  -v, --verbose"
              << "Enable verbosity.\n"
              << std::setw(30) << "  -t, --tickrate=RATE"
              << "Set simulation tickrate (default: 20).\n"
              << std::setw(30) << "  --version"
              << "Prints program's version." << std::endl;
}

void runSimulation(Module module, bool cliMode, bool fast, bool verbosity, bool debug) {
    using namespace std::chrono;

    const auto renderInterval = milliseconds(static_cast<int64_t>(1000 / FPS));
    auto simulationStepTime = microseconds(static_cast<int64_t>(1'000'000 / simulationTickrate));
    auto startTime = high_resolution_clock::now();
    auto nextSimulationTime = high_resolution_clock::now() + simulationStepTime;
    auto lastRenderTime = high_resolution_clock::now();
    u_int64_t simulationStepCount = 0;
    bool running = true;

    while (running) {
        auto currentTime = high_resolution_clock::now();
        auto elapsed = currentTime - startTime;

        while (fast || currentTime >= nextSimulationTime) {
            if (!fast) {
                nextSimulationTime += simulationStepTime;
            }
            simulationStepCount++;

            module.update();

            if (fast) {
                break;
            }
        }

        if (cliMode && (currentTime - lastRenderTime) >= renderInterval) {
            lastRenderTime = currentTime;

            std::cout << "\033[2J\033[1;1H";
            std::cout << std::string(60, '=') << "\n";
            if (debug) {
                std::cout << "Tickrate: " 
                          << std::to_string(
                             1'000'000
                             * simulationStepCount 
                             / static_cast<double>(duration_cast<microseconds>(elapsed).count())) 
                             << "\n";
            }
            std::cout << "Step: " << std::to_string(simulationStepCount) << "\n\n";
            std::cout << reprModule(&module, verbosity) << "\n\n";
        }
    }
}

int main(int argc, char* argv[]) {
    progName = argv[0];
 
    if (argc == 1) {
        usage();
        return 0;
    }

    std::string filePath = "";
    bool verbosity = false;
    bool debug = false;
    bool cliMode = false;
    bool fast = false;

    for (int i = 1; i < argc; i++) {
        const std::string arg = argv[i];

        if (arg[0] == '-') {
            if (arg[1] == '-') {
                std::string op = arg.substr(2);
                if (op == "cli") {
                    cliMode = true;
                } else
                if (op == "debug") {
                    debug = true;
                } else
                if (op == "fast") {
                    fast = true;
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
                } else
                if (startsWith(op, "fps=")) {
                    FPS = std::stod(substrFromChar(op, '='));
                } else {
                    std::cerr << "Invalid option '" << op << "'." << std::endl;
                    return 1;
                }
            } else {
                std::string ops = arg.substr(1);
                for (size_t j = 0; j < ops.size(); j++) {
                    if (j == 0) {
                        if (ops[j] == 'h') {
                            usage();
                            return 0;
                        } else
                        if (ops[j] == 'p') {
                            if (i + 1 >= argc) {
                                std::cerr << "Run at which FPS??" << std::endl;
                                return 1;
                            }
                            FPS = std::stod(argv[i + 1]);
                            break;
                        }
                        if (ops[j] == 't') {
                            if (i + 1 >= argc) {
                                std::cerr << "I require a tickrate definition! :<" << std::endl;
                                return 1;
                            }
                            simulationTickrate = std::stod(argv[i + 1]);

                            if (simulationTickrate >= 100000) {
                                if (!(j + 1 < ops.size() && ops[j + 1] == 'f')) {
                                    std::cerr << "Ooh, that's so big tickrate, Senpai! O.O\n";
                                    std::cerr << "Have you considered to use --fast flag instead?\n";
                                    return 1;
                                }
                            }

                            break;
                        }
                    }
                    if (ops[j] == 'c') {
                        cliMode = true;
                    } else
                    if (ops[j] == 'd') {
                        debug = true;
                    } else
                    if (ops[j] == 'f') {
                        fast = true;
                    } else
                    if (ops[j] == 'v') {
                        verbosity = true;
                    } else {
                        std::cerr << "Invalid option '" << ops[j] << "'." << std::endl;
                        return 1;
                    }
                }
            }
        } else {
            if (filePath.empty()) {
                filePath = arg;
            }
        }
    }

    if (!filePath.empty()) {
        Module module = Module();
        if (!loadModule(module, filePath)) {
            return 1;
        }
        runSimulation(module, cliMode, fast, verbosity, debug);
        return 0;
    } else {
        std::cerr << "Which file do you want me to read? :<\n";
        return 1;
    }
}