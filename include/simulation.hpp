#ifndef simulation_hpp
#define simulation_hpp

#include "module.hpp"

class Simulation {
private:
    static Module *mainModule;
    static Clock clock;
    static Time elapsed;
    static Time nextStepTime;
    static Time stepInterval;

    static RenderWindow window;
    static View view;
    static Time renderInterval;
    static Time lastRenderTime;

    static void renderCLI();
    static void renderGraphical();
    static void updateLogic();
    static void runCLI();
    static void runGraphical();

public:
    struct Flags {
        static bool fast;
        static bool verbose;
        static bool debug;
        static bool cliMode;
    };
    
    static double tickrate;
    static double framerate;
    static uint64_t stepCount;

    static void run(Module *module);
};

#endif