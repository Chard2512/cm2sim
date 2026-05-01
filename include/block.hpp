#ifndef cm2_block_hpp
#define cm2_block_hpp

#include "vector2.hpp"
#include <vector>
#include <string>

enum class BlockID {
    NOR = 0,
    AND = 1,
    OR = 2,
    XOR = 3,
    NAND = 10,
    XNOR = 11,
};

class Block {
protected:
    Vector2 pos = Vector2(0, 0);
    bool state = false;
    std::vector<Block*> inputs = {};
    std::vector<Block*> outputs = {};
    
public:
    Block() = default;
    virtual ~Block() = default;

    Vector2 getPos() const { return pos; }
    void setPos(Vector2 newPos) { pos = newPos; }
    bool getState() const { return state; }
    void setState(bool newState) { state = newState; }
    std::vector<Block*> getInputs() const { return inputs; }
    void addInput(Block* input) {
        inputs.push_back(input);
    }
    std::vector<Block*> getOutputs() const { return outputs; }
    void addOutput(Block* output) {
        outputs.push_back(output);
    }
    virtual bool updateFunction() const {
        return false;
    }
};

class NOR : public Block {

public:
    bool updateFunction() const;
};

class AND : public Block {

public:
    bool updateFunction() const;
};

class OR : public Block {

public:
    bool updateFunction() const;
};

class XOR : public Block {

public:
    bool updateFunction() const;
};

class NAND : public Block {

public:
    bool updateFunction() const;
};

class XNOR : public Block {

public:
    bool updateFunction() const;
};

class BlockFactory {
public:
    static Block* createBlock(
        BlockID id, 
        bool state, 
        Vector2 pos
    ) {
        Block* newBlock = nullptr;
        
        switch (id) {
            case BlockID::NOR:
                newBlock = new NOR();
                break;
            case BlockID::AND:
                newBlock = new AND();
                break;
            case BlockID::OR:
                newBlock = new OR();
                break;
            case BlockID::XOR:
                newBlock = new XOR();
                break;
            case BlockID::NAND:
                newBlock = new NAND();
                break;
            case BlockID::XNOR:
                newBlock = new XNOR();
                break;
            default:
                return nullptr;
        }
        
        newBlock->setPos(pos);
        newBlock->setState(state);
        return newBlock;
    }
};

#endif