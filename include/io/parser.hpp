#ifndef _CM2_PARSER_HPP_
#define _CM2_PARSER_HPP_

#include "core/simulation.hpp"

enum class ArgParseStatus {
    Continue,
    ExitSuccess,
    ExitFailure
};

struct Args {
    std::string moduleFilePath = "";
    SimConfig simConfig;
};

void usage(const std::string& progName);
bool loadModule(Module &module, std::string filepath);
Module* parseSavestring(std::string filepath);
Block* parseBlockstring(std::string blockstring);
ArgParseStatus parseArgs(Args& args, int argc, char* argv[]);

#endif