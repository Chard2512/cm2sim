#ifndef cm2_block_hpp
#define cm2_block_hpp

#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <unordered_map>

using namespace sf;

/* 
How to set a new block:

- Create BlockID
- Create the new block class
- Set the block to be accessed in BlockFactory
- Implement the updateFunction in block.cpp
*/

enum class BlockID {
    NOR = 0,
    AND = 1,
    OR = 2,
    XOR = 3,
    FLIPFLOP = 5,
    NAND = 10,
    XNOR = 11,
    DELAY = 16
};

Color getBlockColor(BlockID blockID);

class Block {
protected:
    Vector2f pos = Vector2f(0, 0);
    bool state = false;
    std::vector<Block*> inputs = {};
    std::vector<Block*> outputs = {};
    
public:
    Block() = default;
    virtual ~Block() = default;

    Vector2f getPosition() const { return pos; }
    void setPosition(Vector2f newPos) { pos = newPos; }
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
    Color getColor() const { return getBlockColor(getID()); };
    virtual bool updateFunction() {
        return false;
    }
    virtual BlockID getID() const = 0;
    virtual std::string getIDName() const = 0;
};

class NOR : public Block {

public:
    bool updateFunction() override;
    BlockID getID() const override { return BlockID::NOR; }
    std::string getIDName() const override { return "NOR"; }
};

class AND : public Block {

public:
    bool updateFunction() override;
    BlockID getID() const override { return BlockID::AND; }
    std::string getIDName() const override { return "AND"; }
};

class OR : public Block {

public:
    bool updateFunction() override;
    BlockID getID() const override { return BlockID::OR; }
    std::string getIDName() const override { return "OR"; }
};

class XOR : public Block {

public:
    bool updateFunction() override;
    BlockID getID() const override { return BlockID::XOR; }
    std::string getIDName() const override { return "XOR"; }
};

class NAND : public Block {

public:
    bool updateFunction() override;
    BlockID getID() const override { return BlockID::NAND; }
    std::string getIDName() const override { return "NAND"; }
};

class XNOR : public Block {

public:
    bool updateFunction() override;
    BlockID getID() const override { return BlockID::XNOR; }
    std::string getIDName() const override { return "XNOR"; }
};

class FLIPFLOP : public Block {
private:
    bool lastEnableState = false;

public:
    bool updateFunction() override;
    BlockID getID() const override { return BlockID::FLIPFLOP; }
    std::string getIDName() const override { return "FLIPFLOP"; }
};

class DELAY : public Block {
private:
    uint32_t delay;
    std::vector<uint32_t> queue;

public:
    bool updateFunction() override;
    void setDelay(uint32_t newDelay) { delay = newDelay; }
    BlockID getID() const override { return BlockID::DELAY; }
    std::string getIDName() const override { return "DELAY"; }
};

class BlockFactory {
public:
    static Block* createBlock(
        BlockID id, 
        bool state, 
        Vector2f pos,
        std::vector<int> properties
    ) {
        Block* newBlock = nullptr;
        
        switch (id) {
            case BlockID::NOR:
            {
                newBlock = new NOR();
                break;
            }
            case BlockID::AND:
            {
                newBlock = new AND();
                break;
            }
            case BlockID::OR:
            {
                newBlock = new OR();
                break;
            }
            case BlockID::XOR:
            {
                newBlock = new XOR();
                break;
            }
            case BlockID::NAND:
            {
                newBlock = new NAND();
                break;
            }
            case BlockID::XNOR:
            {
                newBlock = new XNOR();
                break;
            }
            case BlockID::FLIPFLOP:
            {
                newBlock = new FLIPFLOP();
                break;
            }
            case BlockID::DELAY:
            {
                newBlock = new DELAY();
                DELAY* delayBlock = dynamic_cast<DELAY*>(newBlock);
                uint32_t delay = static_cast<uint32_t>(properties[0]);
                delayBlock->setDelay(delay);
                break;
            }
            default:
            {
                std::cerr << "Not recognized/supported block id '" << static_cast<int>(id) << "'." << std::endl;
                return nullptr;
            }
        }
        
        newBlock->setPosition(pos);
        newBlock->setState(state);
        return newBlock;
    }
};

#endif