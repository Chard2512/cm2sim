#include "cm2core.hpp"

int Block::getId() const { return id; }
Vector2 Block::getPos() const { return pos; }
bool Block::getState() const { return state; }
std::vector<Block*> Block::getInputs() const { return inputs; }
std::vector<Block*> Block::getOutputs() const { return outputs; }

std::vector<Block*> Module::getBlocks() const {
    std::vector<Block*> temp;
    for (Block block : blocks) {
        temp.push_back(&block);
    }
    return temp; 
}