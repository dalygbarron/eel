#include "Builder.hh"

Builder::Builder(Config const *config, Repository *repository) {
    this->config = config;
    this->repository = repository;
}
