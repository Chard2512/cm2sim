#include "core/module.hpp"

Module::Module() {}

Module::~Module() {
    for (auto block : blocks) {
        delete block;
    }
}

std::vector<Block*> Module::getBlocks() const {
    return blocks;
}

Block* Module::getBlock(uint64_t index) const {
    return blocks[index];
}

uint64_t Module::getBlockCount() const {
    return blocks.size();
}

void Module::update() {
    std::vector<std::tuple<NODE*, uint64_t>> nodes = {};
    std::vector<Block*> gates = {};
    for (auto block : blocks) {
        if (block->getID() == BlockID::NODE) {
            auto node = dynamic_cast<NODE*>(block);
            nodes.push_back(std::tuple<NODE*, uint64_t>(node, node->getLevel()));
        } else {
            gates.push_back(block);
        }
    }

    std::sort(nodes.begin(), nodes.end(),
        [](const auto& a, const auto& b) {
            return std::get<1>(a) < std::get<1>(b);
        }
    );

    for (auto gate : gates) {
        gate->update();
    }
    for (auto gate : gates) {
        gate->step();
    }

    bool stableNodes;
    do {
        stableNodes = true;
        for (auto node : nodes) {
            bool previousState = std::get<0>(node)->state;
            std::get<0>(node)->update();
            std::get<0>(node)->step();
            if (previousState != std::get<0>(node)->state) { stableNodes = false; }
        }
    } while (!stableNodes);

    for (auto node : nodes) {
        std::get<0>(node)->interacted = false;
    }
}