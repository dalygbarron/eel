/**
 * Dedicated to managing the scene stack and the main loop of the game.
 */
#ifndef GAME_H
#define GAME_H

#include "src/model/Engine.h"

/**
 * Run a scene transition on the current scene stack.
 * @param engine     is the engine (and scene stack) to run the transition on.
 * @param transition is the transition string to run.
 */
void game_transition(struct Engine *engine, char const *transition);

/**
 * Run one frame of the game on the given engine.
 * @param engine is the instance of game to run.
 * @return true if the frame was nice, and false if the engine has run to
 *         completion.
 */
int game_frame(struct Engine *engine);

#endif
