#include "simulation.hpp"
#include "cliview.hpp"
#include "sfmlview.hpp"

Module *Simulation::mainModule;
Clock Simulation::clock;
RenderWindow Simulation::window;
View Simulation::view;
Time Simulation::elapsed = microseconds(0);
Time Simulation::nextStepTime = microseconds(0);
Time Simulation::renderInterval;
Time Simulation::lastRenderTime = microseconds(0);
Time Simulation::stepInterval;

bool Simulation::Flags::cliMode = false;
bool Simulation::Flags::debug = false;
bool Simulation::Flags::fast = false;
bool Simulation::Flags::verbose = false;

double Simulation::framerate = 60;
double Simulation::tickrate = 20;

uint64_t Simulation::stepCount = 0;

void Simulation::updateLogic() {
    while (Flags::fast || elapsed >= nextStepTime) {
        if (!Flags::fast) {
            nextStepTime += stepInterval;
        }

        stepCount++;

        mainModule->update();

        if (Flags::fast) {
            break;
        }
    }
}

void Simulation::renderCLI() {
    if ((elapsed - lastRenderTime) >= renderInterval) {
        lastRenderTime = elapsed;
        std::cout << "\033[2J\033[1;1H";
        std::cout << std::string(60, '=') << "\n";

        if (Flags::debug) {
            if (!Flags::fast) {
            std::cout << "Tickrate: " 
                        << static_cast<float>(
                            1'000'000.f
                            * stepCount
                            / ((elapsed.asMicroseconds() / stepInterval.asMicroseconds()) * stepInterval.asMicroseconds()))
                            << "\n";
            } else {
                std::cout << "Tickrate: " 
                        << static_cast<float>(
                            1'000'000.f
                            * stepCount
                            / elapsed.asMicroseconds())
                            << "\n";                       
            }
        }
        std::cout << "Step: " << std::to_string(stepCount) << "\n\n";
        std::cout << reprModule(mainModule, Flags::verbose) << "\n\n";
    }
}

void Simulation::runCLI() {
    bool running = true;
    std::cout << std::fixed << std::setprecision(1);

    while (running) {
        elapsed = clock.getElapsedTime();

        updateLogic();
        renderCLI();
    }
}

void Simulation::renderGraphical() {
    if ((elapsed - lastRenderTime) >= renderInterval) {
        lastRenderTime = elapsed;

        window.clear();
        SFMLView::renderModule(&window, mainModule);
        window.setView(view);
        window.display();
    }
}

void Simulation::runGraphical() {
    // Fix hardwired initialization
    window = RenderWindow(VideoMode({960, 544}), "SFCM2");
    view = View(Vector2f(0, 0), Vector2f(32, 18));

    window.setFramerateLimit(0);

    Vector2i previousMousePos;

    bool draggingView = false;

    while (window.isOpen()) {
        elapsed = clock.getElapsedTime();
        while (const std::optional event = window.pollEvent()) {
            if (event->is<Event::Closed>()) {
                window.close();
            } else
            if (const auto* pressed = event->getIf<Event::MouseButtonPressed>()) {
                if (pressed->button == Mouse::Button::Right) {
                    draggingView = true;

                    previousMousePos = Mouse::getPosition(window);
                }
            } else
            if (const auto* released = event->getIf<Event::MouseButtonReleased>()) {
                if (released->button == Mouse::Button::Right) {
                    draggingView = false;
                }
            } else
            if (const auto* moved = event->getIf<sf::Event::MouseMoved>()) {
                if (draggingView) {
                    sf::Vector2i currentMousePos(moved->position.x, moved->position.y);
                    
                    // Calculate movement delta in world coordinates
                    sf::Vector2f delta = window.mapPixelToCoords(currentMousePos) -
                                        window.mapPixelToCoords(previousMousePos);
                    
                    // Move view opposite to mouse movement
                    view.move(-delta);
                    
                    previousMousePos = currentMousePos;
                }
            } else
            if (const auto* scrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
                if (scrolled->wheel == Mouse::Wheel::Vertical) {
                    float delta = scrolled->delta;

                    Vector2i mousePixelPos = Mouse::getPosition(window);

                    Vector2f beforeZoom = window.mapPixelToCoords(mousePixelPos);

                    float zoomFactor = 1.0f * powf(0.7, delta);

                    view.zoom(zoomFactor);

                    Vector2f afterZoom = window.mapPixelToCoords(mousePixelPos, view);

                    view.move(beforeZoom - afterZoom);
                }
            }
        }

        updateLogic();
        renderGraphical();
    }
}

void Simulation::run(Module *module) {
    clock = Clock();
    mainModule = module;
    Simulation::renderInterval = milliseconds(1'000 / framerate);
    Simulation::stepInterval = microseconds(1'000'000 / tickrate);

    if (Flags::cliMode) {
        runCLI();
    } else {
        runGraphical();
    }
}