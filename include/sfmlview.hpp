#ifndef sfmlview_hpp
#define sfmlview_hpp

#include "block.hpp"
#include "module.hpp"

class SFMLView {
private:
    static RectangleShape getBlockRectangle(Block* block);
    static RectangleShape getConnectionLine(Block* block0, Block* block1);
    static void renderConnection(RenderWindow* window, Block* block0, Block* block1);
    static void renderBlock(RenderWindow* window, Block* block);

public:
    static void renderModule(RenderWindow* window, Module* module);
};

#endif