#ifndef _CM2_SIMULATION_HPP_
#define _CM2_SIMULATION_HPP_

#include <thread>
#include <atomic>
#include <mutex>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include "core/module.hpp"
#include "render/renderer.hpp"
#include "user/camera.hpp"
#define WINDOW_NAME "SFCM2"

struct SimConfig {
    double tickrate = 20, framerate = 60;
    unsigned FOV = 18; // How many blocks can be filled vertically?
    sf::Vector2u windowDims = sf::Vector2u(960, 544);
};

class Simulation {
private:
    friend class CameraService;

    sf::RenderWindow window;
    sf::View view;
    Renderer renderer;
    Module* mainModule;
    SimConfig config;

    CameraService cameraService;

    void handleEvents();
    void updateView();
public:
    explicit Simulation(SimConfig cfg);
    ~Simulation();
    void run(Module* module);
};

#endif