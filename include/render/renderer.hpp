#ifndef _CM2_RENDERER_HPP_
#define _CM2_RENDERER_HPP_

#include <unordered_map>
#include <SFML/Graphics/RenderWindow.hpp>
#include "core/module.hpp"

class Renderer {
private:
    sf::Color getBlockIDColor(BlockID blockID);
    sf::Color getBlockColor(Block* block);
    sf::RectangleShape getBlockRectangle(Block* block);
    sf::RectangleShape getConnectionRectangle(Block* block0, Block* block1);
    void renderBlock(sf::RenderWindow* window, Block* block);
    void renderConnection(sf::RenderWindow* window, Block* block0, Block* block1);
public:
    void render(sf::RenderWindow* window, Module* module);
};

#endif