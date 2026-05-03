#include <iostream>
#include <iomanip>
#include <filesystem>
#include "strutils.hpp"
#include "parser.hpp"
#include "simulation.hpp"
#define PROJECT_NAME "sfcm2"
#define VERSION "0.1"

const auto GLOBAL_CLOCK = Clock(); // To be removed

std::string progName;

void usage() {
    std::cout << "Usage: " << progName << " [OPTION]... [FILE]\n";
    std::cout << "Run a simulation of a Circuit Maker 2 module.\n\n";
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
              << "Set simulation framerate (default: 60).\n"
              << std::setw(30) << "  -h, --help"
              << "Prints this help message.\n"
              << std::setw(30) << "  -v, --verbose"
              << "Enable verbosity.\n"
              << std::setw(30) << "  -t, --tickrate=RATE"
              << "Set simulation tickrate (default: 20).\n"
              << std::setw(30) << "  --version"
              << "Prints program's version." << std::endl;
}

void send(std::string text, bool enable) {
    if (enable) {
        std::streamsize oldPrecision = std::cout.precision();
        std::cout << std::fixed << std::setprecision(3);
        auto elapsed = GLOBAL_CLOCK.getElapsedTime().asMilliseconds() / 1000.f;
        std::cout << std::left << "[" << elapsed << std::setw(4) << "] " << text << "\n";
        std::cout.precision(oldPrecision);
    }
}

int main(int argc, char* argv[]) {
    progName = argv[0];
 
    if (argc == 1) {
        usage();
        return 0;
    }

    std::string filePath = "";

    for (int i = 1; i < argc; i++) {
        const std::string arg = argv[i];

        if (arg[0] == '-') {
            if (arg[1] == '-') {
                std::string op = arg.substr(2);
                if (op == "cli") {
                    Simulation::Flags::cliMode = true;
                } else
                if (op == "debug") {
                    Simulation::Flags::debug = true;
                } else
                if (op == "fast") {
                    Simulation::Flags::fast = true;
                } else
                if (op == "help") {
                    usage();
                    return 0;
                } else
                if (op == "verbose") {
                    Simulation::Flags::verbose = true;
                } else
                if (op == "version") {
                    std::cout << PROJECT_NAME << " " << VERSION << std::endl;
                    return 0;
                } else
                if (startsWith(op, "tickrate=")) {
                    Simulation::tickrate = std::stod(substrFromCharStart(op, '='));
                } else
                if (startsWith(op, "fps=")) {
                    Simulation::framerate = std::stod(substrFromCharStart(op, '='));
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
                            Simulation::framerate = std::stod(argv[i + 1]);
                            i++;
                            break;
                        }
                        if (ops[j] == 't') {
                            if (i + 1 >= argc) {
                                std::cerr << "I require a tickrate definition! :<" << std::endl;
                                return 1;
                            }
                            Simulation::tickrate = std::stod(argv[i + 1]);
                            i++;

                            if (Simulation::tickrate > 1000000) {
                                std::cerr << "Ooh, that's too big tickrate, Senpai! O.O\n";
                                std::cerr << "I can't handle that much without --fast flag...\n";
                                return 1;
                            }

                            break;
                        }
                    }
                    if (ops[j] == 'c') {
                        Simulation::Flags::cliMode = true;
                    } else
                    if (ops[j] == 'd') {
                        Simulation::Flags::debug = true;
                    } else
                    if (ops[j] == 'f') {
                        Simulation::Flags::fast = true;
                    } else
                    if (ops[j] == 'v') {
                        Simulation::Flags::verbose = true;
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
        std::filesystem::path p(filePath);
        if (!std::filesystem::exists(p)) {
            std::cerr << "The file doesn't exist." << std::endl;
            return 1;
        }
        
        std::string ext = substrFromCharEnd(filePath, '.');
        if (!ext.empty() && ext != "txt") {
            std::cerr << "Hmm... that doesn't look like something I can read." << std::endl;
            return 1;
        }

        Module module = Module();
        if (!loadModule(module, filePath)) {
            return 1;
        }
        Simulation::run(&module);
        return 0;
    } else {
        std::cerr << "Which file do you want me to run? :<" << std::endl;
        return 1;
    }
}