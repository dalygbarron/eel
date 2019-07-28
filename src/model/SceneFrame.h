#ifndef SCENE_FRAME_H
#define SCENE_FRAME_H

#define SceneFrame_TYPE_PLAIN 0
#define SceneFrame_TYPE_JUMP 1
#define SceneFrame_TYPE_BOAT 2
#define SceneFrame_TYPE_ADVENTURE 3

/**
 * Holds together the data and logic of a scene.
 */
struct SceneFrame {
    /** The type of scene that this is, based on a numerical code */
    int type;

    /** Top element of the scene's current gui if it has one */
    struct Control *control;

    /** Next scene in the scene stack */
    struct SceneFrame *next;

    /** Pointer to the scene's content */
    void *scene;
};

#endif
