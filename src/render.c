#include "src/render.h"
#include "src/model/Engine.h"
#include "src/model/Display.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>

static int initialised = 0;

struct Display *render_createDisplay(int width, int height, char const *title) {
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
        initialised = 1;
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
    SDL_GLContext *context = SDL_GL_CreateContext(window);
    if (!context) {
        // TODO: log error.
        SDL_DestroyWindow(window);
        return 0;
    }
    struct Display *display = malloc(sizeof(struct Display));
    display->window = window;
    display->context = context;
    return display;
}

void render_destroyDisplay(struct Display *display) {
    SDL_DestroyWindow(display->window);
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

void render_frame(struct Engine const *engine, struct Display const *display) {
    struct SceneFrame *scene = engine->scenes;
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if (scene) {
        // TODO: render the scene.
    }
}
