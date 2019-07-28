#ifndef ENGINE_H
#define ENGINE_H

/**
 * Stores the game's scene stack and core variables.
 */
struct Engine {
    struct SceneFrame *scenes;
    int time;
}

#endif
