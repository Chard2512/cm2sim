#ifndef cm2_parser_hpp
#define cm2_parser_hpp

#include "module.hpp"

bool loadModule(Module& module, std::string filepath);
Block* parseBlockstring(std::string blockstring);

#endif