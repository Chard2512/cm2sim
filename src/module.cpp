#include "module.hpp"

Module::Module() {}

std::vector<Block*> Module::getBlocks() const {
    std::vector<Block*> temp;
    for (Block block : blocks) {
        temp.push_back(const_cast<Block*>(&block));
    }
    return temp; 
}

Block* Module::getBlock(int index) const {
    return const_cast<Block*>(&blocks[index]);
}

void Module::update() {
    std::vector<bool> nextState = {};
    for (size_t i = 0; i < blocks.size(); i++) {
        nextState.push_back(blocks[i].updateFunction());
    }
    for (size_t i = 0; i < blocks.size(); i++) {
        blocks[i].setState(nextState[i]);
    }
}