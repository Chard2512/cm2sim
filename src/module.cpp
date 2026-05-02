#include "module.hpp"

Module::Module() {}

std::vector<Block*> Module::getBlocks() const {
    return blocks;
}

Block* Module::getBlock(int index) const {
    return blocks[index];
}

void Module::update() {
    std::vector<bool> nextState = {};
    for (size_t i = 0; i < blocks.size(); i++) {
        nextState.push_back(blocks[i]->updateFunction());
    }
    for (size_t i = 0; i < blocks.size(); i++) {
        blocks[i]->setState(nextState[i]);
    }
}