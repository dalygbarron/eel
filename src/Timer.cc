#include "Timer.hh"
#include "spdlog/spdlog.h"
#include <SFML/System.hpp>

Timer::Timer() {
    this->tick = 0;
    this->clock.restart();
    for (int i = 0; i < Constant::TIMER_LIMIT - 1; i++) {
        this->timers[i].listener = 0;
        this->timers[i].content.next = this->timers + i + 1;
    }
    this->timers[Constant::TIMER_LIMIT - 1].listener = 0;
    this->timers[Constant::TIMER_LIMIT - 1].content.next = 0;
    this->emptyTimer = this->timers;
}

void Timer::update() {
    this->tick++;
    // update waiters.
    for (int i = 0; i < Constant::TIMER_LIMIT; i++) {
        if (this->timers[i].listener && this->timers[i].content.time == this->tick) {
            this->timers[i].listener->listen(Signal(Signal::TYPE_TIMED));
            this->timers[i].listener = 0;
            this->timers[i].content.next = this->emptyTimer;
            this->emptyTimer = this->timers + i;
        }
    }
    // monitor ticks per second.
    if (!(this->tick % 300)) {
        float fps = 300.0 / clock.getElapsedTime().asSeconds();
        if (fps < Constant::FPS_WARN) spdlog::warn("FPS: {}", fps);
        else spdlog::debug("FPS: {}", fps);
        this->clock.restart();
    }
}

void Timer::start(Listener *listener, long time) {
    if (!this->emptyTimer) {
        spdlog::error("Trying to start timer but all are in use");
    } else {
        Wait *next = this->emptyTimer->content.next;
        this->emptyTimer->listener = listener;
        this->emptyTimer->content.time = this->tick + time;
        this->emptyTimer = next;
    }
}
