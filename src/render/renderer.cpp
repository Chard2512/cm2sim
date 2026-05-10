#include <unordered_map>
#include "render/renderer.hpp"

sf::Color Renderer::getBlockIDColor(BlockID blockID) {
    static const std::unordered_map<BlockID, sf::Color> colorMap = {
        {BlockID::NOR,      sf::Color(255, 9, 0, 255)},
        {BlockID::AND,      sf::Color(0, 121, 255, 255)},
        {BlockID::OR,       sf::Color(0, 241, 29, 255)},
        {BlockID::XOR,      sf::Color(168, 0, 255, 255)},
        {BlockID::BUTTON,   sf::Color(255, 127, 0, 255)},
        {BlockID::NAND,     sf::Color(0, 42, 89, 255)},
        {BlockID::XNOR,     sf::Color(213, 0, 103, 255)},
        {BlockID::RANDOM,   sf::Color(84, 54, 35, 255)},
        {BlockID::LED,      sf::Color(255, 255, 255, 255)},
        {BlockID::FLIPFLOP, sf::Color(30, 30, 30, 255)},
        {BlockID::NODE,     sf::Color(165, 177, 200, 255)},
        {BlockID::DELAY,    sf::Color(98, 24, 148, 255)}
    };

    return colorMap.at(blockID);
}

sf::Color Renderer::getBlockColor(Block* block) {
    return getBlockIDColor(block->getID());
}

sf::RectangleShape Renderer::getBlockRectangle(Block* block) {
    sf::RectangleShape blockRectangle = sf::RectangleShape();
    blockRectangle.setPosition(block->getPosition());
    blockRectangle.setSize({1, 1});

    sf::Color baseColor = getBlockColor(block);
    sf::Color outlineColor = sf::Color(
        baseColor.r * 0.2f,
        baseColor.g * 0.2f,
        baseColor.b * 0.2f,
        baseColor.a
    );

    blockRectangle.setOutlineThickness(-0.05);
    blockRectangle.setOutlineColor(outlineColor);

    if (block->getState()) {
        blockRectangle.setFillColor(baseColor);
    } else {
        sf::Color darkColor = sf::Color(
            baseColor.r * 0.3f,
            baseColor.g * 0.3f,
            baseColor.b * 0.3f,
            baseColor.a
        );
        blockRectangle.setFillColor(darkColor);
    }

    return blockRectangle;
}

void Renderer::renderBlock(sf::RenderWindow* window, Block* block) {
    sf::RectangleShape blockRectangle = getBlockRectangle(block);
    window->draw(blockRectangle);
}

sf::RectangleShape Renderer::getConnectionRectangle(Block* block0, Block* block1) {
    float length = std::hypot(
        block1->getPosition().x - block0->getPosition().x, 
        block1->getPosition().y - block0->getPosition().y
    );

    sf::Color lineBaseColor = getBlockColor(block0);
    lineBaseColor.a = 127;

    sf::RectangleShape line(sf::Vector2f(length, 0.2f));
    if (block0->getState()) {
        line.setFillColor(lineBaseColor);
    } else {
        sf::Color darkerLineColor = sf::Color(
            lineBaseColor.r * 0.25f,
            lineBaseColor.g * 0.25f,
            lineBaseColor.b * 0.25f,
            lineBaseColor.a
        );
        line.setFillColor(darkerLineColor);
    }

    line.setOrigin(sf::Vector2f(0, 0.1f));
    line.setPosition(block0->getPosition());
    line.move(sf::Vector2f(0.5, 0.5)); // The block Rectangle might have different size, fix this later

    auto angle = sf::radians(
        std::atan2(
            block1->getPosition().y - block0->getPosition().y,
            block1->getPosition().x - block0->getPosition().x
        )
    );

    line.setRotation(angle);
    return line;
}

void Renderer::renderConnection(sf::RenderWindow* window, Block* block0, Block* block1) {
    sf::RectangleShape connectionRectangle = getConnectionRectangle(block0, block1);
    window->draw(connectionRectangle, sf::BlendMax);
}

void Renderer::render(sf::RenderWindow* window, Module* module) {
    for (Block* block : module->getBlocks()) {
        auto outputs = block->getOutputs();
        for (auto output : outputs) {
            renderConnection(window, block, output);
        }
    }
    for (Block* block : module->getBlocks()) {
        renderBlock(window, block);
    } 
}