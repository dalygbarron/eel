#include "src/render.h"
#include "src/model/Window.h"
#include <SDL.h>
#include <SDL_opengl.h>

static int initialised = false;

sfWindow render_createWindow(int width, int height, char const *title) {
    // The first time SDL will have to be initialised.
    if (!initialised) {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            // TODO: log error.
            return 0;
        }
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
        SDL_GL_SetAttribute(
            SDL_GL_CONTEXT_PROFILE_MASK,
            SDL_GL_CONTEXT_PROFILE_CORE
        );
        if (SDL_GL_SetSwapInterval(1) < 0) {
            // TODO: log error.
        }
        initialised = true;
    }
    // now make the window and context.
    SDL_Window *window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );
    if (!window) {
        // TODO: log error.
        return 0;
    }
    context = SDL_GL_CreateContext(window);
    if (!context) {
        // TODO: log error.
        SDL_DestroyWindow(window);
        return 0;
    }
    struct Window *windowObject = malloc(sizeof(struct Window));
    windowObject->window = window;
    windowObject->context = context;
    return windowObject;
}

void render_destroyWindow(struct Window *window) {
    // TODO: shit.
}

void render_initSpriteArray(
    struct SpriteArray *spriteArray,
    //sfTexture *texture,
    int n
) {
    // TODO: shit.
}

void render_freeSpriteArray(struct SpriteArray *spriteArray) {
    // TODO: shit.
}
