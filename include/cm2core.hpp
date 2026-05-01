#ifndef cm2core_hpp
#define cm2core_hpp

#include "vector2.hpp"
#include <vector>

class Block {
protected:
    int id;
    Vector2 pos;
    bool state;
    std::vector<Block*> inputs;
    std::vector<Block*> outputs;
    
public:
    int getId() const;
    Vector2 getPos() const;
    bool getState() const;
    std::vector<Block*> getInputs() const;
    std::vector<Block*> getOutputs() const;
    virtual void update();
};

class Module {
private:
    std::vector<Block> blocks;

public:
    std::vector<Block*> getBlocks() const;
    void update();
};

#endif