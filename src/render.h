#ifndef RENDER_H
#define RENDER_H

#include "src/model/Sprite.h"
#include "src/model/SpriteArray.h"

/**
 * Creates a window and returns it.
 * NB: this function has a little bit of global state because the first time it
 *     runs it has to check if SDL has been globally initialised yet and if it
 *     hasn't then it does it.
 * @param width  is the width of the window in pixels.
 * @param height is the height of the window in pixels.
 * @param title  is the title text to be placed upon the window.
 * @return the new window.
 */
struct Window render_createWindow(int width, int height, char const *title);

/**
 * Closes a window and clears it's memeory.
 * @param window is the window to destroy.
 */
void render_destroyWindow(struct Window *window);

/**
 * Sets up a sprite array.
 * @param spriteArray is the sprite array to be set up.
 * @param n           is the number of sprites that it will support.
 */
void render_initSpriteArray(
    struct SpriteArray *spriteArray,
    //sfTexture *texture,
    int n
);

/**
 * Takes back the memory being used by a sprite array's free list.
 * @param spriteArray is the spriteArray to free.
 */
void render_freeSpriteArray(struct SpriteArray *spriteArray);

/**
 * Creates a new sprite in a sprite array.
 * @param spriteArray is the sprite array to create it in.
 * @param sprite      is the sprite object to store the new sprite in.
 */
void render_addSprite(struct SpriteArray *spriteArray, struct Sprite *sprite);

/**
 * Adds a transformation to a sprite's transformation.
 * @param sprite    is the sprite to transform.
 * @param transform is the transformation to apply.
 */
void render_addTransform(struct Sprite *sprite, struct Transform transform);

/**
 * Sets a sprite's transformation.
 * @param sprite    is the sprite to do it to.
 * @param transform is the transformation to set it to.
 */
void render_setTransform(struct Sprite *sprite, struct Transform transform);


#endif
