#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "Texture.hh"

/**
 * Contains a window and rendering stuff needed to do the graphics.
 */
namespace Graphics {
    static const int WIDTH = 1024;
    static const int HEIGHT = 600;

    /**
     * Starts up the game window and rendering stuff.
     * @param title is the title of the game window.
     */
    void init(char const *title);

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
     * @param width  is the width of the texture.
     * @param height is the height of the texture.
     */
    Texture *createTexture(int width, int height);
};

#endif
