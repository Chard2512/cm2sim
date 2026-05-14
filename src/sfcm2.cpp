#include <iostream>
#include <iomanip>
#include <filesystem>
#include "io/strutils.hpp"
#include "io/parser.hpp"
#include "core/simulation.hpp"

int main(int argc, char* argv[]) {
    Args args;
    ArgParseStatus argParseStatus = parseArgs(args, argc, argv);

    if (argParseStatus == ArgParseStatus::ExitSuccess) { return 0; }
    if (argParseStatus == ArgParseStatus::ExitFailure) { return 1; }

    std::string filePath = args.moduleFilePath;
    
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

        Module* module = new Module();
        if (!loadModule(*module, filePath)) {
            delete module;
            return 1;
        }
        Simulation sim(args.simConfig);
        sim.run(module);
        return 0;
    } else {
        std::cerr << "Which file do you want me to run? :<" << std::endl;
        return 1;
    }
}