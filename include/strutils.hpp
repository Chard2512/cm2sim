#ifndef strutils_hpp
#define strutils_hpp

#include <vector>
#include <string>

std::vector<std::string> split(std::string text, const char sep);
std::string substrFromChar(std::string text, const char sep);
bool startsWith(std::string text, const std::string match);

#endif strutils_hpp