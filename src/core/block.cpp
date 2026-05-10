#include "core/block.hpp"

sf::FloatRect Block::getRect() {
    return sf::FloatRect(
        this->position,
        sf::Vector2f(1, 1)
    );
}

void NOR::update() {
    for (Block* input : inputs) {
        if (input->getState() == true) {
            nextState = false ^ interacted;
            interacted = false;
            return;
        }
    }
    nextState = true ^ interacted;
    interacted = false;
}

void AND::update() {
    for (Block* input : inputs) {
        if (input->getState() == false) {
            nextState = false ^ interacted;
            interacted = false;
            return;
        }
    }
    nextState = true ^ interacted;
    interacted = false;
}

void OR::update() {
    for (Block* input : inputs) {
        if (input->getState() == true) {
            nextState = true ^ interacted;
            interacted = false;
            return;
        }
    }
    nextState = false ^ interacted;
    interacted = false;
}

void XOR::update() {
    bool tmp = false;
    for (Block* input : inputs) {
        if (input->getState() == true) {
            tmp = !tmp;
        }
    }
    nextState = tmp ^ interacted;
    interacted = false;
}

void BUTTON::update() {
    nextState = interacted;
    interacted = false;
}

void FLIPFLOP::update() {
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

    nextState = state ^ enable ^ interacted;
    interacted = false;
}

void LED::update() {
    for (Block* input : inputs) {
        if (input->getState() == true) {
            nextState = true ^ interacted;
            interacted = false;
            return;
        }
    }
    nextState = false ^ interacted;
    interacted = false;
}

void NAND::update() {
    for (Block* input : inputs) {
        if (input->getState() == false) {
            nextState = true ^ interacted;
            interacted = false; 
            return;
        }
    }
    nextState = false ^ interacted;
    interacted = false;
}

void XNOR::update() {
    bool tmp = true;
    for (Block* input : inputs) {
        if (input->getState() == true) {
            tmp = !tmp;
        }
    }
    nextState = tmp ^ interacted;
    interacted = false;
}

void RANDOM::update() {
    nextState = Random::get().next<bool>(probability) ^ interacted;
    interacted = false;
}

void DELAY::update() {
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

    nextState = consumed ^ interacted;
    interacted = false;
}

void NODE::update() {
    for (Block* input : inputs) {
        if (input->getState() == true) {
            nextState = true;
            return;
        }
    }
    nextState = false || interacted;
}

uint64_t NODE::getLevel() {
    if (cachedLevel.has_value()) {
        return cachedLevel.value();
    }

    // Prevent infinite recursion on circular dependencies
    if (visiting) {
        return 0;
    }

    visiting = true;

    std::vector<Block*> nodes;
    for (auto input : inputs) {
        if (input->getID() == BlockID::NODE) {
            nodes.push_back(input);
        }
    }

    if (nodes.size() == 0) {
        cachedLevel = 0;
        visiting = false;
        return 0; 
    }

    uint64_t maxLevel = 0;
    for (auto block : nodes) {
        auto node = dynamic_cast<NODE*>(block);
        maxLevel = std::max(maxLevel, node->getLevel());
    }

    cachedLevel = maxLevel + 1;
    visiting = false;
    return maxLevel + 1;
}

Block* BlockFactory::createBlock(
        BlockID id, 
        bool state, 
        sf::Vector2f pos,
        std::vector<float> properties
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
        case BlockID::BUTTON:
        {
            newBlock = new BUTTON();
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
        case BlockID::RANDOM:
        {
            float probability;
            if (properties.size() == 0) {
                probability = 0.5f;
            } else {
                probability = std::min(std::max(static_cast<float>(properties[0]), 0.f), 1.f);
            }

            newBlock = new RANDOM();
            RANDOM* randomBlock = dynamic_cast<RANDOM*>(newBlock);
            randomBlock->probability = probability;
            break;
        }
        case BlockID::FLIPFLOP:
        {
            newBlock = new FLIPFLOP();
            break;
        }
        case BlockID::LED:
        {
            newBlock = new LED();
            break;
        }
        case BlockID::NODE:
        {
            newBlock = new NODE();
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
            delayBlock->delay = delay;
            break;
        }
        default:
        {
            std::cerr << "ERROR: Not recognized/supported block id '" << static_cast<int>(id) << "'." << std::endl;
            return nullptr;
        }
    }
    
    newBlock->position = pos;
    newBlock->state = state;
    return newBlock;
}