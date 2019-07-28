#ifndef ENGINE_H
#define ENGINE_H

/**
 * Stores the game's scene stack and core variables.
 */
struct Engine {
    /** start of linked stack of scenes */
    struct SceneFrame *scenes;

    /** the number of elapsed frames */
    long time;
};

#endif
