#include "sfmlview.hpp"

RectangleShape SFMLView::getBlockRectangle(Block* block) {
    RectangleShape blockRectangle = RectangleShape();
    blockRectangle.setPosition(block->getPosition());
    blockRectangle.setSize({1, 1});

    Color baseColor = block->getColor();
    Color outlineColor = Color(
        static_cast<uint8_t>(baseColor.r * 0.2f),
        static_cast<uint8_t>(baseColor.g * 0.2f),
        static_cast<uint8_t>(baseColor.b * 0.2f),
        baseColor.a
    );

    blockRectangle.setOutlineThickness(-0.05);
    blockRectangle.setOutlineColor(outlineColor);

    if (block->getState()) {
        blockRectangle.setFillColor(baseColor);
    } else {
        Color darkColor = Color(
            static_cast<uint8_t>(baseColor.r * 0.3f),
            static_cast<uint8_t>(baseColor.g * 0.3f),
            static_cast<uint8_t>(baseColor.b * 0.3f),
            baseColor.a
        );
        blockRectangle.setFillColor(darkColor);
    }

    return blockRectangle;
}

void SFMLView::renderBlock(RenderWindow* window, Block* block) {
    RectangleShape blockRectangle = getBlockRectangle(block);
    window->draw(blockRectangle);
}

RectangleShape SFMLView::getConnectionLine(Block* block0, Block* block1) {
    float length = std::hypot(
        block1->getPosition().x - block0->getPosition().x, 
        block1->getPosition().y - block0->getPosition().y
    );

    RectangleShape line(Vector2f(length, 0.1f));
    if (block0->getState()) {
        line.setFillColor(Color(255, 255, 255, 255));
    } else {
        line.setFillColor(Color(63, 63, 63, 255));
    }

    line.setOrigin(Vector2f(0, 0.1f));
    line.setPosition(block0->getPosition());
    line.move(Vector2f(0.5, 0.5)); // The block Rectangle might have different size, fix this later

    auto angle = radians(
        std::atan2(
            block1->getPosition().y - block0->getPosition().y,
            block1->getPosition().x - block0->getPosition().x
        )
    );

    line.setRotation(angle);
    return line;
}

void SFMLView::renderConnection(RenderWindow* window, Block* block0, Block* block1) {
    RectangleShape connectionLine = getConnectionLine(block0, block1);
    window->draw(connectionLine);
}

void SFMLView::renderModule(RenderWindow* window, Module* module) {
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