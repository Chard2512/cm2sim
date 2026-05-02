#ifndef cliview_hpp
#define cliview_hpp

#include "block.hpp"
#include "module.hpp"

std::string reprBlock(Block* block, bool verbose);
std::string reprModule(Module* module, bool verbose);

#endif