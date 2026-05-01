#ifndef cm2_module_hpp
#define cm2_module_hpp

#include "block.hpp"

class Module {
private:
    std::vector<Block> blocks;

public:
    std::vector<Block*> getBlocks() const;
    void update();
};

#endif