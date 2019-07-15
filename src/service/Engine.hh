#ifndef ENGINE_H
#define ENGINE_H

#include "service/Config.hh"
#include "service/Timer.hh"
#include "service/Radio.hh"
#include "service/Status.hh"
#include "service/builder/ControlBuilder.hh"

/**
 * Encapsulates gamewide services as needed by scenes.
 */
class Engine {
public:
    Config const *config;
    ControlBuilder const *controlBuilder;
    Timer *timer;
    Radio *radio;
    Status *status;
    Repository *repository;

    /**
     * Builds the engine and puts in all of it's dependencies in one swoop.
     * @param config         is the configuration.
     * @param timer          is the timer.
     * @param radio          is the audio controller.
     * @param status         is the game status.
     * @param repository     is the asset repositoey.
     * @param controlBuilder is the control builder.
     */
    Engine(
        Config const *config,
        Timer *timer,
        Radio *radio,
        Status *status,
        Repository *repository,
        ControlBuilder const *controlBuilder
    );
};

#endif
