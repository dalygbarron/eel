/**
 * Dedicated to managing the scene stack and the main loop of the game.
 */
#ifndef GAME_H
#define GAME_H

#include "src/model/Engine.h"

/**
 * Creates a new engine.
 * @param transition describes the first scene of the game. Must be a push
 *                   transition unless you want issues.
 * @return the new engine.
 */
struct Engine *game_createEngine(char const *transition);

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

/**
 * Processes all of the recent input events and sends them to listeners in the engine.
 * @param engine is the engine that the events are going to.
 * @return false if the quit button has been pressed, otherwise true.
 */
int game_handleInput(struct Engine *engine);

#endif
