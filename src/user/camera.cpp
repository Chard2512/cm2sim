#include "user/camera.hpp"
#include "core/simulation.hpp"

CameraService::CameraService(Simulation* _simulation) {
    simulation = _simulation;
}

CameraService::~CameraService() {
    simulation = nullptr;
}

void CameraService::moveCamera(const std::optional<sf::Event> event) {
    if (const auto* pressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (pressed->button == sf::Mouse::Button::Right) {
            dragging = true;

            previousMousePos = sf::Mouse::getPosition(simulation->window);
        }
    } else
    if (const auto* released = event->getIf<sf::Event::MouseButtonReleased>()) {
        if (released->button == sf::Mouse::Button::Right) {
            dragging = false;
        }
    } else
    if (const auto* moved = event->getIf<sf::Event::MouseMoved>()) {
        if (dragging) {
            sf::Vector2i currentMousePos(moved->position.x, moved->position.y);
            
            // Calculate movement delta in world coordinates
            sf::Vector2f delta = simulation->window.mapPixelToCoords(currentMousePos)
                                 - simulation->window.mapPixelToCoords(previousMousePos);
            
            // Move view opposite to mouse movement
            simulation->view.move(-delta);
            simulation->updateView();
            
            previousMousePos = currentMousePos;
        }
    }
}

void CameraService::zoomCamera(const std::optional<sf::Event> event) {
    if (const auto* scrolled = event->getIf<sf::Event::MouseWheelScrolled>()) {
        if (scrolled->wheel == sf::Mouse::Wheel::Vertical) {
            float delta = scrolled->delta;

            sf::Vector2i mousePixelPos = sf::Mouse::getPosition(simulation->window);
            sf::Vector2f beforeZoom = simulation->window.mapPixelToCoords(mousePixelPos);
            float zoomFactor = 1.0f * powf(0.7, delta);

            simulation->view.zoom(zoomFactor);

            sf::Vector2f afterZoom = simulation->window.mapPixelToCoords(mousePixelPos, simulation->view);
            simulation->view.move(beforeZoom - afterZoom);
            simulation->updateView();
        }
    }
}

void CameraService::resizeViewToWindow(const std::optional<sf::Event> event) {
    if (const auto* resize = event->getIf<sf::Event::Resized>()) {
        float windowRatio = static_cast<float>(resize->size.x) / static_cast<float>(resize->size.y);

        simulation->view.setSize(sf::Vector2f(windowRatio * simulation->view.getSize().y, simulation->view.getSize().y));
        simulation->updateView();
    }
}

void CameraService::handleEvent(const std::optional<sf::Event> event) {
    moveCamera(event);
    zoomCamera(event);
    resizeViewToWindow(event);
}