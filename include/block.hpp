#ifndef cm2_block_hpp
#define cm2_block_hpp

#include "vector2.hpp"
#include <vector>

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
    int id;
    Vector2 pos = Vector2(0, 0);
    bool state = false;
    std::vector<Block*> inputs = {};
    std::vector<Block*> outputs = {};
    
public:
    int getId() const { return id; }
    Vector2 getPos() const { return pos; }
    bool getState() const { return state; }
    void setState(bool newState) { state = newState; }
    std::vector<Block*> getInputs() const { return inputs; }
    std::vector<Block*> getOutputs() const { return outputs; }
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