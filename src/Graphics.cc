#include "Graphics.hh"

#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/gl.h>

SDL_Window *window = 0;
SDL_GLContext context;

void Graphics::init(char const *title) {
    // init sdl
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize: " << SDL_GetError() << std::endl;
        throw -1;
    }
    // Use OpenGL 2.1
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    //Create window
    window = SDL_CreateWindow(
        title,
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        Graphics::WIDTH,
        Graphics::HEIGHT,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "window could not be created: " << SDL_GetError() << std::endl;
        throw -1;
    }
    //Create context
    context = SDL_GL_CreateContext(window);
    if (!context) {
        std::cerr << "context could not be created: " << SDL_GetError() << std::endl;
        throw -1;
    }
    //Use Vsync
    if (SDL_GL_SetSwapInterval(1) < 0) {
        std::cerr << "can't do vsync: " << SDL_GetError() << std::endl;
        throw -1;
    }
    // now do open gl setting up stuff
    glViewport(0, 0, Graphics::WIDTH, Graphics::HEIGHT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, Graphics::WIDTH, Graphics::HEIGHT, 0, 1, -1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0, 0, 0, 1);
    glEnable(GL_TEXTURE_2D);
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "Error starting opengl: " << error << std::endl;
        throw -1;
    }
}

void Graphics::close() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Graphics::clear() {
     glClear(GL_COLOR_BUFFER_BIT);
}


void Graphics::flip() {
    SDL_GL_SwapWindow(window);
}

Texture *Graphics::createTexture(int width, int height) {
    int n = width * height;
    GLuint board[n];
    for (int i = 0; i < n; i++) {
        board[i] = (GLuint)((i / width & 16 ^ i % height & 16) ? 0xffffffff : 0xffff0000);
    }
    Texture *texture = new Texture;
    if (!texture->loadFromPixels(board, width, height)) {
        std::cerr << "Could not load texture." << std::endl;
    }
    return texture;
}
