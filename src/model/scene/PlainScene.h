#ifndef PLAIN_SCENE_H
#define PLAIN_SCENE_H

#include "src/model/ScriptRunner.h"

/**
 * Data for a scene that just runs a script.
 */
struct PlainScene {
    struct ScriptRunner *script;
};

#endif
