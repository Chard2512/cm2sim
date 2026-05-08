#ifndef _CM2_CAMERA_HPP_
#define _CM2_CAMERA_HPP_

#include <optional>
#include <SFML/Window/Event.hpp>

class Simulation;

class CameraService {
private:
    bool dragging = false;
    sf::Vector2i previousMousePos;

    void moveCamera(const std::optional<sf::Event> event);
    void zoomCamera(const std::optional<sf::Event> event);
    void resizeViewToWindow(const std::optional<sf::Event> event);
    Simulation* simulation;

public:
    explicit CameraService(Simulation* _simulation);
    ~CameraService();
    void handleEvent(const std::optional<sf::Event> event);
};

#endif