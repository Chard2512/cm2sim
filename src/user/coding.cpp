#include <iostream>
#include "user/coding.hpp"
#include "core/simulation.hpp"
#include "io/parser.hpp"

CodingService::CodingService(Simulation* _simulation) {
    simulation = _simulation;
    timeSinceLastCheck = sf::seconds(0);
    lastWrite = fs::last_write_time(simulation->config.moduleFilePath);
}

CodingService::~CodingService() {
    simulation = nullptr;
}

void CodingService::updateModule() {
    Module* newModule = new Module();
    if (loadModule(*newModule, simulation->config.moduleFilePath.string())) {
        delete simulation->mainModule;
        simulation->mainModule = newModule;
    } else {
        delete newModule;
    }
}

void CodingService::monitor() {
    timeSinceLastCheck += simulation->deltaTime;
    if (timeSinceLastCheck >= sf::seconds(1)) { // Check each 1 second
        timeSinceLastCheck = sf::Time::Zero;
        auto currentWrite = fs::last_write_time(simulation->config.moduleFilePath);

        if (currentWrite != lastWrite) {
            lastWrite = currentWrite;
            updateModule();
        }
    }
}

void CodingService::handleEvent() {
    monitor();
}