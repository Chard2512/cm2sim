#include <iostream>
#include <fstream>
#include <string>
#include "parser.hpp"
#include "strutils.hpp"

bool loadModule(Module& module, std::string filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "ERROR: Could not open file \"" << filepath << "\"." << std::endl; 
        return false;
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

    return true;
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