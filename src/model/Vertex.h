#ifndef VERTEX_H
#define VERTEX_H

#include <SDL2/SDL_opengl.h>

/**
 * Represents a single vertex going to the GPU.
 */
struct Vertex {
    /** location of the vertex */
    GLfloat pos[3];

    /**
     * location on the texture if there is one that the vertex has */
    GLfloat texturePos[2];

    /** colour modifier of the vertex */
    GLubyte colour[4];
};

#endif
