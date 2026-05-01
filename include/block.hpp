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

class Block {
protected:
    BlockID id;
    Vector2 pos = Vector2(0, 0);
    bool state = false;
    std::vector<Block*> inputs = {};
    std::vector<Block*> outputs = {};
    
public:
    Block();

    BlockID getId() const { return id; }
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
    virtual bool updateFunction() const;
};

class NOR : public Block {
protected:
    int id = 0;

public:
    bool updateFunction() const;
};

class AND : public Block {
protected:
    int id = 1;

public:
    bool updateFunction() const;
};

class OR : public Block {
protected:
    int id = 2;

public:
    bool updateFunction() const;
};

class XOR : public Block {
protected:
    int id = 3;

public:
    bool updateFunction() const;
};

class NAND : public Block {
protected:
    int id = 10;

public:
    bool updateFunction() const;
};

class XNOR : public Block {
protected:
    int id = 11;

public:
    bool updateFunction() const;
};

#endif