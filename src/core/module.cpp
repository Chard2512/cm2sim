#include "core/module.hpp"

Module::Module() {}

Module::~Module() {
    for (auto block : blocks) {
        delete block;
    }
}

std::vector<Block*> Module::getBlocks() const {
    return blocks;
}

Block* Module::getBlock(uint64_t index) const {
    return blocks[index];
}

uint64_t Module::getBlockCount() const {
    return blocks.size();
}

void Module::update() {
    std::vector<bool> nextState = {};
    nextState.reserve(blocks.size());
    for (size_t i = 0; i < blocks.size(); i++) {
        nextState.push_back(blocks[i]->update());
    }
    for (size_t i = 0; i < blocks.size(); i++) {
        blocks[i]->setState(nextState[i]);
    }
}