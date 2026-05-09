#include "user/interaction.hpp"
#include "core/simulation.hpp"

InteractionService::InteractionService(Simulation* _simulation) {
    simulation = _simulation;
}

InteractionService::~InteractionService() {
    simulation = nullptr;
}

void InteractionService::blockInteract(const std::optional<sf::Event> event) {
    if (const auto* pressed = event->getIf<sf::Event::MouseButtonPressed>()) {
        if (pressed->button == sf::Mouse::Button::Left) {
            const auto clickPixel = sf::Mouse::getPosition();
            const auto clickCoords = simulation->window.mapPixelToCoords(clickPixel);

            for (auto block : simulation->mainModule->getBlocks()) {
                if (block->getRect().contains(clickCoords)) {
                    block->interact();
                }
            }
        }
    }
}

void InteractionService::handleEvent(const std::optional<sf::Event> event) {
    blockInteract(event);
}