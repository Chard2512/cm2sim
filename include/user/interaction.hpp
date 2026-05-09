#ifndef _CM2_INTERACTION_HPP_
#define _CM2_INTERACTION_HPP_

#include <optional>
#include <SFML/Window/Event.hpp>

class Simulation;

class InteractionService {
private:
    void blockInteract(const std::optional<sf::Event> event);
    Simulation* simulation;

public:
    explicit InteractionService(Simulation* _simulation);
    ~InteractionService();
    void handleEvent(const std::optional<sf::Event> event);
};

#endif