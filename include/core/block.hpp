#ifndef _CM2_BLOCK_HPP_
#define _CM2_BLOCK_HPP_

#include <memory>
#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <unordered_map>

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

sf::Color getBlockColor(BlockID blockID);

class Block {
protected:
    sf::Vector2f position = sf::Vector2f(0, 0);
    bool state = false;
    std::vector<Block*> inputs = {};
    std::vector<Block*> outputs = {};
    
public:
    Block() = default;
    virtual ~Block() = default;

    sf::Vector2f getPosition() const { return position; }
    void setPosition(sf::Vector2f newPosition) { position = newPosition; }
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
    virtual bool update() {
        return false;
    }
    virtual BlockID getID() const = 0;
    virtual std::string getIDName() const = 0;
};

class NOR : public Block {

public:
    bool update() override;
    BlockID getID() const override { return BlockID::NOR; }
    std::string getIDName() const override { return "NOR"; }
};

class AND : public Block {
public:
    bool update() override;
    BlockID getID() const override { return BlockID::AND; }
    std::string getIDName() const override { return "AND"; }
};

class OR : public Block {

public:
    bool update() override;
    BlockID getID() const override { return BlockID::OR; }
    std::string getIDName() const override { return "OR"; }
};

class XOR : public Block {

public:
    bool update() override;
    BlockID getID() const override { return BlockID::XOR; }
    std::string getIDName() const override { return "XOR"; }
};

class NAND : public Block {

public:
    bool update() override;
    BlockID getID() const override { return BlockID::NAND; }
    std::string getIDName() const override { return "NAND"; }
};

class XNOR : public Block {

public:
    bool update() override;
    BlockID getID() const override { return BlockID::XNOR; }
    std::string getIDName() const override { return "XNOR"; }
};

class FLIPFLOP : public Block {
private:
    bool lastEnableState = false;

public:
    bool update() override;
    BlockID getID() const override { return BlockID::FLIPFLOP; }
    std::string getIDName() const override { return "FLIPFLOP"; }
};

class DELAY : public Block {
private:
    uint32_t delay;
    std::vector<uint32_t> queue;

public:
    bool update() override;
    void setDelay(uint32_t newDelay) { delay = newDelay; }
    BlockID getID() const override { return BlockID::DELAY; }
    std::string getIDName() const override { return "DELAY"; }
};

class BlockFactory {
public:
    static Block* createBlock(
        BlockID id, 
        bool state, 
        sf::Vector2f pos,
        std::vector<int> properties
    );
};

#endif