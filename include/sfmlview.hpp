#ifndef sfmlview_hpp
#define sfmlview_hpp

#include "block.hpp"
#include "module.hpp"

class SFMLView {
private:
    static RectangleShape getBlockRectangle(Block* block);
    static void renderBlock(RenderWindow* window, Block* block);

public:
    static void renderModule(RenderWindow* window, Module* module);
};

#endif