#ifndef sfmlview2_hpp
#define sfmlview2_hpp

#include "block.hpp"
#include "module.hpp"

class Camera2 {
public:
    Vector2f pos;
    double zoom; // How many blocks can you fit vertically?

    Camera2(Vector2f ipos, double izoom): pos(ipos), zoom(izoom) {}
};

class SFMLView2 {
private:
    static RenderWindow window;
    static Camera2 camera;
    static uint worldToScreen(double len);
    static Vector2u worldToScreen(Vector2f pos);
    static RectangleShape getBlockRectangle(Block* block);
    static void renderBlock(Block* block);

public:
    static void init();
    static void renderModule(Module* module);
    static void clearScreen();
    static void display();
    static void catchEvents();
    static bool isWindowOpen();
};

#endif