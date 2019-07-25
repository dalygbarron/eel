#ifndef RENDER_H
#define RENDER_H

/**
 * Creates a window and returns it.
 * @param width  is the width of the window in pixels.
 * @param height is the height of the window in pixels.
 * @param title  is the title text to be placed upon the window.
 * @return the new window.
 */
sfWindow render_createWindow(int width, int height, char const *title);

/**
 * Sets up a sprite array.
 * @param spriteArray is the sprite array to be set up.
 * @param texture     is the texture that it will use.
 * @param n           is the number of sprites that it will support.
 */
void render_initSpriteArray(
    struct SpriteArray *spriteArray,
    sfTexture *texture,
    int n
);

/**
 * Takes back the memory being used by a sprite array's free list.
 * @param spriteArray is the spriteArray to free.
 */
void render_freeSpriteArray(struct SpriteArray *spriteArray);

#endif
