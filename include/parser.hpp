#ifndef cm2_parser_hpp
#define cm2_parser_hpp

#include "module.hpp"

bool loadModule(Module module, std::string filepath);
std::vector<std::string> split(std::string text, const char sep);
Block parseBlockstring(std::string blockstring);

#endif