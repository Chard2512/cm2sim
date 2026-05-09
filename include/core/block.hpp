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
    NODE = 15,
    DELAY = 16
};

class Block {
protected:
    friend class Module;
    friend class BlockFactory;

    sf::Vector2f position = sf::Vector2f(0, 0);
    bool state, nextState = false;
    bool interacted = false;
    std::vector<Block*> inputs = {};
    std::vector<Block*> outputs = {};
    
    void step() { state = nextState; }
    void addInput(Block* input) {
        inputs.push_back(input);
    }
    void addOutput(Block* output) {
        outputs.push_back(output);
    }
    virtual void update() {
        return;
    }

public:
    Block() = default;
    virtual ~Block() = default;

    sf::Vector2f getPosition() const { return position; }
    bool getState() const { return state; }
    const std::vector<Block*>& getInputs() const { return inputs; }
    const std::vector<Block*>& getOutputs() const { return outputs; }
    sf::FloatRect getRect();
    void interact() { interacted = true; }
    virtual BlockID getID() const = 0;
    virtual std::string getIDName() const = 0;
};

class NOR : public Block {

public:
    void update() override;
    BlockID getID() const override { return BlockID::NOR; }
    std::string getIDName() const override { return "NOR"; }
};

class AND : public Block {
public:
    void update() override;
    BlockID getID() const override { return BlockID::AND; }
    std::string getIDName() const override { return "AND"; }
};

class OR : public Block {

public:
    void update() override;
    BlockID getID() const override { return BlockID::OR; }
    std::string getIDName() const override { return "OR"; }
};

class XOR : public Block {

public:
    void update() override;
    BlockID getID() const override { return BlockID::XOR; }
    std::string getIDName() const override { return "XOR"; }
};

class NAND : public Block {

public:
    void update() override;
    BlockID getID() const override { return BlockID::NAND; }
    std::string getIDName() const override { return "NAND"; }
};

class XNOR : public Block {

public:
    void update() override;
    BlockID getID() const override { return BlockID::XNOR; }
    std::string getIDName() const override { return "XNOR"; }
};

class FLIPFLOP : public Block {
private:
    bool lastEnableState = false;

public:
    void update() override;
    BlockID getID() const override { return BlockID::FLIPFLOP; }
    std::string getIDName() const override { return "FLIPFLOP"; }
};

class DELAY : public Block {
private:
    friend class BlockFactory;

    uint32_t delay;
    std::vector<uint32_t> queue;

public:
    void update() override;

    BlockID getID() const override { return BlockID::DELAY; }
    std::string getIDName() const override { return "DELAY"; }
};

class NODE : public Block {
private:
    std::optional<uint64_t> cachedLevel;
    bool visiting = false;

public:
    void update() override;
    BlockID getID() const override { return BlockID::NODE; }
    std::string getIDName() const override { return "NODE"; }
    uint64_t getLevel();
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