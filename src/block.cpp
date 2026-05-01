#include "block.hpp"

bool NOR::updateFunction() const {
    for (Block* input : inputs) {
        if (input->getState() == true) {
            return false;
        }
    }
    return true;
}

bool AND::updateFunction() const {
    for (Block* input : inputs) {
        if (input->getState() == false) {
            return false;
        }
    }
    return true;
}

bool OR::updateFunction() const {
    for (Block* input : inputs) {
        if (input->getState() == true) {
            return true;
        }
    }
    return false;
}

bool XOR::updateFunction() const {
    bool tmp = false;
    for (Block* input : inputs) {
        if (input->getState() == true) {
            tmp = !tmp;
        }
    }
    return tmp;
}

bool XNOR::updateFunction() const {
    bool tmp = true;
    for (Block* input : inputs) {
        if (input->getState() == true) {
            tmp = !tmp;
        }
    }
    return tmp;
}