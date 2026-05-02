#include "cliview.hpp"
#include "block.hpp"
#include "module.hpp"

std::string reprBlock(Block* block, bool verbose) {
    if (!verbose) {
        return block->getIDName() + "(" + std::to_string(block->getState()) + ")";
    } else {
        return block->getIDName() 
               + "(state=" + std::to_string(block->getState()) 
               + ", pos=(" + std::to_string(block->getPosition().x) + ", " + std::to_string(block->getPosition().y) + ")"
               + ")";
    }
}

std::string reprModule(Module* module, bool verbose) {
    std::string buffer = "";

    std::vector<Block*> blocks = module->getBlocks();
    for (size_t i = 0; i < blocks.size(); i++) {
        buffer += std::to_string(i) + ": " + reprBlock(blocks[i], verbose);
        if (i != blocks.size() - 1) {
            buffer += "\n";
        }
    }

    return buffer;
}