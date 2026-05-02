#ifndef cm2_module_hpp
#define cm2_module_hpp

#include "block.hpp"

class Module {
private:
    std::vector<Block*> blocks = {};

public:
    Module();

    std::vector<Block*> getBlocks() const;
    Block* getBlock(int index) const;
    void addBlock(Block* block) { blocks.push_back(block); };
    void connectBlocks(Block* block0, Block* block1) { 
        block0->addOutput(block1);
        block1->addInput(block0);
    };
    void update();
};

#endif