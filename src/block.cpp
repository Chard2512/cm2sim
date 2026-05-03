#include "block.hpp"


Color getBlockColor(BlockID blockID) {
    static const std::unordered_map<BlockID, Color> colorMap = {
        {BlockID::NOR,  Color(255, 9, 0, 255)},
        {BlockID::AND,  Color(0, 121, 255, 255)},
        {BlockID::OR,   Color(0, 241, 29, 255)},
        {BlockID::XOR,  Color(168, 0, 255, 255)},
        {BlockID::NAND, Color(0, 42, 89, 255)},
        {BlockID::XNOR, Color(213, 0, 103, 255)},
        {BlockID::FLIPFLOP, Color(30, 30, 30, 255)}
    };

    return colorMap.at(blockID);
}

bool NOR::updateFunction() {
    for (Block* input : inputs) {
        if (input->getState() == true) {
            return false;
        }
    }
    return true;
}

bool AND::updateFunction() {
    for (Block* input : inputs) {
        if (input->getState() == false) {
            return false;
        }
    }
    return true;
}

bool OR::updateFunction() {
    for (Block* input : inputs) {
        if (input->getState() == true) {
            return true;
        }
    }
    return false;
}

bool NAND::updateFunction() {
    for (Block* input : inputs) {
        if (input->getState() == false) {
            return true;
        }
    }
    return false;
}

bool XOR::updateFunction() {
    bool tmp = false;
    for (Block* input : inputs) {
        if (input->getState() == true) {
            tmp = !tmp;
        }
    }
    return tmp;
}

bool XNOR::updateFunction() {
    bool tmp = true;
    for (Block* input : inputs) {
        if (input->getState() == true) {
            tmp = !tmp;
        }
    }
    return tmp;
}

bool FLIPFLOP::updateFunction() {
    bool enable = false;
    for (Block* input : inputs) {
        if (input->getState() == true) {
            enable = true;
            break;
        }
    }
    bool tmp = enable;
    enable &= !lastEnableState;
    lastEnableState = tmp;

    return state ^ enable;
}