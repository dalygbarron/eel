#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Texture.hh"

/**
 * Contains a window and rendering stuff needed to do the graphics.
 */
namespace Graphics {
    static const int WIDTH = 1024;
    static const int HEIGHT = 768;

    /**
     * Starts up the game window and rendering stuff.
     * @param title      is the title of the game window.
     * @param fullscreen tells you if the window should be fullscreen or just a window ya know.
     */
    void init(char const *title, int fullscreen);

    /**
     * Closes the game window and rendering stuff.
     */
    void close();

    /**
     * Covers the screen in black.
     */
    void clear();

    /**
     * Puts the rendered stuff onto the screen.
     */
    void flip();

    /**
     * Makes a nice checkerboard picture for you.
     * @param size contains the dimensions of the texture to create.
     */
    Texture *createTexture(Vector2 size);

    /**
     * Loads a picture from a file and returns it to you as a texture.
     * @param filename is the filename of the picture.
     */
    Texture *loadTextureFile(char const *filename);
};

#endif
