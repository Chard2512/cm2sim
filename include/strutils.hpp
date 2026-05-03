#ifndef strutils_hpp
#define strutils_hpp

#include <vector>
#include <string>

std::vector<std::string> split(std::string text, const char sep);
std::string substrFromCharStart(std::string text, const char sep);
std::string substrFromCharEnd(std::string text, const char sep);
bool startsWith(std::string text, const std::string match);

#endif