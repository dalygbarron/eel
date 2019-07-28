#ifndef SCENE_FRAME_H
#define SCENE_FRAME_H

/**
 * Holds together the data and logic of a scene.
 */
struct SceneFrame {
    /** The type of scene that this is, based on a numerical code */
    int type;

    /** Pointer to the scene's content */
    void *scene;
};

#endif
