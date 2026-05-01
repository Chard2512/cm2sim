#include <iostream>
#include <fstream>
#include <string>
#include "parser.hpp"

Module loadModule(std::string filepath) {
    Module module = Module();
    
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "ERROR: Could not open file \"" << filepath << "\"." << std::endl; 
        return module;
    }

    std::string savestring;
    std::getline(file, savestring);

    auto fields = split(savestring, '?');
    auto blockstrings = split(fields[0], ';');
    auto wirestrings = split(fields[1], ';');

    for (auto blockstring : blockstrings) {
        module.addBlock(parseBlockstring(blockstring));
    }

    for (auto wirestring : wirestrings) {
        auto blocksStr = split(wirestring, ',');
        int block0Index = std::stoi(blocksStr[0]) - 1;
        int block1Index = std::stoi(blocksStr[1]) - 1;
        Block* block0 = module.getBlock(block0Index);
        Block* block1 = module.getBlock(block1Index);
        module.connectBlocks(block0, block1);
    }

    return module;
}

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

Block parseBlockstring(std::string blockstring) {
    std::vector<std::string> blockParams = split(blockstring, ',');
    BlockID blockID = static_cast<BlockID>(std::stoi(blockParams[0]));
    bool state = static_cast<bool>(std::stoi(blockParams[1]));
    Vector2 pos = Vector2(
        std::stod(blockParams[2]),
        std::stod(blockParams[4])
    );
    return *BlockFactory::createBlock(blockID, state, pos);
}