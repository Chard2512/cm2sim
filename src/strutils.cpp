#include "strutils.hpp"

std::vector<std::string> split(std::string text, const char sep) {
    std::vector<std::string> result;
    std::string current;
    for (char c : text) {
        if (c == sep) {
            result.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }

    result.push_back(current);

    return result;
}

std::string substrFromChar(std::string text, const char sep) {
    return text.substr(text.find('=') + 1);
}

bool startsWith(std::string text, const std::string match) {
    return (text.find(match) == 0);
}