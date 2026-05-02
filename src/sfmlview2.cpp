#include "sfmlview2.hpp"

void SFMLView2::init() {
    // TODO: Fix hardwired initialization
    window = sf::RenderWindow(
        sf::VideoMode({960, 544}),
        "SFCM2"
    );

    camera = Camera2(Vector2f(0, 0), 10);
}

uint SFMLView2::worldToScreen(double len) {
    return window.getSize().y * (len / camera.zoom);
}

Vector2u SFMLView2::worldToScreen(Vector2f pos) {
    return Vector2u(
        worldToScreen(pos.x) + window.getSize().x / 2,
        worldToScreen(pos.y) + window.getSize().y / 2
    );
}

RectangleShape SFMLView2::getBlockRectangle(Block* block) {
    Vector2u blockScreenCenter = worldToScreen(block->getPosition());
    uint size = worldToScreen(1); // Any block has size 1 by default

    RectangleShape blockRectangle = RectangleShape();
    blockRectangle.setPosition(block->getPosition());
    blockRectangle.setSize({size, size});
    blockRectangle.setOutlineThickness(1);
    blockRectangle.setOutlineColor(Color(0x000000));
    // Change this to correspond to blockID
    if (block->getState()) {
        blockRectangle.setFillColor(Color(0xffffff)); 
    } else {
        blockRectangle.setFillColor(Color(0xeeeeee)); 
    }

    return blockRectangle;
}

void SFMLView2::renderBlock(Block* block) {
    RectangleShape blockRectangle = getBlockRectangle(block);
    window.draw(blockRectangle);
}

void SFMLView2::renderModule(Module* module) {
    for (Block* block : module->getBlocks()) {
        renderBlock(block);
    } 
}

void SFMLView2::clearScreen() {
    window.clear();
}

void SFMLView2::display() {
    window.display();
}

void SFMLView2::catchEvents() {
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }
    }
}

bool SFMLView2::isWindowOpen() {
    return window.isOpen();
}