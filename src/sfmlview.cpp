#include "sfmlview.hpp"

RectangleShape SFMLView::getBlockRectangle(Block* block) {
    RectangleShape blockRectangle = RectangleShape();
    blockRectangle.setPosition(block->getPosition());
    blockRectangle.setSize({1, 1});
    blockRectangle.setOutlineThickness(-0.05);
    blockRectangle.setOutlineColor(Color(0x111111ff));
    // Change this to correspond to blockID
    if (block->getState()) {
        blockRectangle.setFillColor(Color(0xffffffff)); 
    } else {
        blockRectangle.setFillColor(Color(0x222222ff)); 
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