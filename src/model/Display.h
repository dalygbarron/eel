#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL.h>
#include <SDL_opengl.h>

/**
 * Stores the stuff that is needed for rendering.
 */
struct Display {
    SDL_Window *window;
    SDL_GLContext *context;
};

#endif
