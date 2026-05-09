#include "core/block.hpp"

sf::FloatRect Block::getRect() {
    return sf::FloatRect(
        this->position,
        sf::Vector2f(1, 1)
    );
}

bool NOR::update() {
    for (Block* input : inputs) {
        if (input->getState() == true) {
            return false;
        }
    }
    return true;
}

bool AND::update() {
    for (Block* input : inputs) {
        if (input->getState() == false) {
            return false;
        }
    }
    return true;
}

bool OR::update() {
    for (Block* input : inputs) {
        if (input->getState() == true) {
            return true;
        }
    }
    return false;
}

bool NAND::update() {
    for (Block* input : inputs) {
        if (input->getState() == false) {
            return true;
        }
    }
    return false;
}

bool XOR::update() {
    bool tmp = false;
    for (Block* input : inputs) {
        if (input->getState() == true) {
            tmp = !tmp;
        }
    }
    return tmp;
}

bool XNOR::update() {
    bool tmp = true;
    for (Block* input : inputs) {
        if (input->getState() == true) {
            tmp = !tmp;
        }
    }
    return tmp;
}

bool FLIPFLOP::update() {
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

bool DELAY::update() {
    bool enable = false;
    for (Block* input : inputs) {
        if (input->getState() == true) {
            enable = true;
            break;
        }
    }
    if (enable) {
        queue.push_back(0);
    }

    bool consumed = false;
    for (size_t i = 0; i < queue.size(); i++) {
        queue[i]++;
        if (queue[i] >= delay) {
            std::swap(queue[i], queue.back());
            queue.pop_back();
            consumed = true;
            i--;
        }
    }

    return consumed;
}

Block* BlockFactory::createBlock(
        BlockID id, 
        bool state, 
        sf::Vector2f pos,
        std::vector<int> properties
    ) 
{
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
            uint32_t delay;
            if (properties.size() == 0) {
                delay = 20;
            } else {
                delay = static_cast<uint32_t>(properties[0]);

                if (delay > 1000) {
                    std::cout << "WARNING: Delay block contains a delay property value superior to allowed (1000)." 
                              << " This will be simulated, but consider to set it down.\n";
                }
            }

            newBlock = new DELAY();
            DELAY* delayBlock = dynamic_cast<DELAY*>(newBlock);
            delayBlock->setDelay(delay);
            break;
        }
        default:
        {
            std::cerr << "ERROR: Not recognized/supported block id '" << static_cast<int>(id) << "'." << std::endl;
            return nullptr;
        }
    }
    
    newBlock->setPosition(pos);
    newBlock->setState(state);
    return newBlock;
}