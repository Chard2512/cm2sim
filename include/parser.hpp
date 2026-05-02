#ifndef cm2_parser_hpp
#define cm2_parser_hpp

#include <optional>
#include "module.hpp"

bool loadModule(Module& module, std::string filepath);
std::optional<Block> parseBlockstring(std::string blockstring);

#endif