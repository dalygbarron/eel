#include "Input.hh"

#include <SDL2/SDL.h>

// NB: the idea with having this two level system is that the sdl key codes can be customised for different controls.
const int KEY_CODE_UP = SDLK_UP;
const int KEY_CODE_DOWN = SDLK_DOWN;
const int KEY_CODE_LEFT = SDLK_LEFT;
const int KEY_CODE_RIGHT = SDLK_RIGHT;
const int KEY_CODE_FIRE = SDLK_z;
const int KEY_CODE_STRAFE = SDLK_LSHIFT;
const int KEY_CODE_BOMB = SDLK_x;
const int KEY_CODE_PAUSE = SDLK_ESCAPE;

unsigned char down[Input::BUTTON_N];
unsigned char fresh[Input::BUTTON_N];

int Input::process() {
    // nuke new press table.
    for (int i = 0; i < BUTTON_N; i++) fresh[i] = 0;
    // respond to events.
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            return false;
        } if (e.type == SDL_KEYDOWN) {
            int button = -1;
            if (e.key.keysym.sym == KEY_CODE_UP) button = Input::BUTTON_UP;
            if (e.key.keysym.sym == KEY_CODE_DOWN) button = Input::BUTTON_DOWN;
            if (e.key.keysym.sym == KEY_CODE_LEFT) button = Input::BUTTON_LEFT;
            if (e.key.keysym.sym == KEY_CODE_RIGHT) button = Input::BUTTON_RIGHT;
            if (e.key.keysym.sym == KEY_CODE_FIRE) button = Input::BUTTON_FIRE;
            if (e.key.keysym.sym == KEY_CODE_BOMB) button = Input::BUTTON_BOMB;
            if (e.key.keysym.sym == KEY_CODE_STRAFE) button = Input::BUTTON_STRAFE;
            if (button >= 0) {
                down[button] = true;
                fresh[button] = true;
            }
        }
    }
    return true;
}

int Input::isDown(int button) {
    return down[button];
}

int Input::isRecentlyDown(int button) {
    return fresh[button];
}
