#ifndef _CM2_MODULE_HPP_
#define _CM2_MODULE_HPP_

#include <memory>
#include "core/block.hpp"

class Module {
private:
    std::vector<Block*> blocks = {};

public:
    Module();
    ~Module();

    std::vector<Block*> getBlocks() const;
    Block* getBlock(uint64_t index) const;
    void addBlock(Block* block) { blocks.push_back(block); };
    void connectBlocks(Block* block0, Block* block1) { 
        block0->addOutput(block1);
        block1->addInput(block0);
    };
    void update();
};

#endif