#include <thread>
#include <mutex>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Graphics/Color.hpp>
#include "core/simulation.hpp"

Simulation::Simulation(SimConfig cfg)
    :   config(cfg),
        cameraService(this),
        interactionService(this)
{}

Simulation::~Simulation() {
    mainModule = nullptr;
}

void Simulation::handleEvents() {
    while (const std::optional<sf::Event> event = window.pollEvent()) {
        // Exit
        if (event->is<sf::Event::Closed>()) {
            window.close();
        } else
        if (auto keypress = event->getIf<sf::Event::KeyPressed>()) {
            if (keypress->code == sf::Keyboard::Key::Q) {
                window.close();
            }
        }

        cameraService.handleEvent(event);
        interactionService.handleEvent(event);
    }
}

void Simulation::updateView() {
    window.setView(view);
}

void Simulation::run(Module* module) {
    const sf::Time TIME_PER_UPDATE = sf::seconds(1.f / config.tickrate);
    const sf::Time TIME_PER_RENDER = sf::seconds(1.f / config.framerate);
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    sf::Time timeSinceLastRender = sf::Time::Zero;

    mainModule = module;

    window = sf::RenderWindow(sf::VideoMode(config.windowDims), WINDOW_NAME);
    const float windowRatio = window.getSize().x / window.getSize().y;
    view = sf::View(sf::Vector2f(0, 0), sf::Vector2f(windowRatio * config.FOV, config.FOV));
    window.setView(view);

    while (window.isOpen()) {
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;
        timeSinceLastRender += elapsedTime;

        handleEvents();

        while (timeSinceLastUpdate >= TIME_PER_UPDATE) {
            timeSinceLastUpdate -= TIME_PER_UPDATE;

            module->update();
        }  

        if (timeSinceLastRender >= TIME_PER_RENDER) {
            timeSinceLastRender = sf::Time::Zero;

            window.clear();
            renderer.render(&window, mainModule);
            window.display();
        }
    }
}