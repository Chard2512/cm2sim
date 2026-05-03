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

void SFMLView::renderModule(RenderWindow* window, Module* module) {
    for (Block* block : module->getBlocks()) {
        renderBlock(window, block);
    } 
}