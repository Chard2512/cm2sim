
#ifndef _CM2_CODING_HPP_
#define _CM2_CODING_HPP_

#include <optional>
#include <filesystem>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Time.hpp>

namespace fs = std::filesystem;

class Simulation;

class CodingService {
private:
    fs::file_time_type lastWrite; 
    sf::Time timeSinceLastCheck;

    void updateModule();
    void monitor();
    Simulation* simulation;

public:
    explicit CodingService(Simulation* _simulation);
    ~CodingService();
    void handleEvent();
};

#endif