#ifndef RENDER_H
#define RENDER_H

#include "src/model/Sprite.h"
#include "src/model/Engine.h"
#include "src/model/Display.h"
#include "src/model/Stage.h"

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
struct Display *render_createDisplay(int width, int height, char const *title);

/**
 * Closes a window and clears it's memeory.
 * @param display is the window to destroy.
 */
void render_destroyDisplay(struct Display *display);

/**
 * Creates a stage for you to use.
 * @param maxSprites is the maximum number of sprites this stage can have.
 * @param maxTiles   is the maximum number of tiles this stage can have.
 * @return the new stage.
 */
struct Stage *render_createStage(int maxSprites, int maxTiles);

/**
 * Frees a stage's memory and all it's sprites and tiles and stuff.
 * Does not free it's texture or shader.
 */
void render_destroyStage(struct Stage *stage);

/**
 * Creates a new sprite in a stage..
 * @param stage is the stage to create it in.
 * @return the new sprite.
 */
struct Sprite *render_addSprite(struct Stage *stage);

/**
 * Frees the memory of a sprite and takes it out of the stage it is in.
void render_destroySprite(struct Sprite *sprite);

struct Tile *render_addTile(struct Stage *stage);

void render_destroyTile(struct Tile *tile);

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

/**
 * Renders the current state of the game to the screen.
 * @param engine  is the game state to display.
 * @param display is the screen and stuff to display it onto.
 */
void render_frame(struct Engine const *engine, struct Display const *display);

#endif
