#include "service/Engine.hh"

Engine::Engine(
    Config const *config,
    Radio *radio,
    Status *status,
    Repository *repository,
    ControlBuilder const *controlBuilder
) {
    this->config = config;
    this->radio = radio;
    this->status = status;
    this->repository = repository;
    this->controlBuilder = controlBuilder;
}
