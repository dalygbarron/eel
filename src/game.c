#include "src/game.h"
#include "src/log.h"
#include "src/model/SceneFrame.h"
#include "src/model/Engine.h"
#include <SDL2/SDL.h>
#include <stdlib.h>

static void *createPlainScene(char const *transition) {
    struct PlainScene *scene = malloc(sizeof(struct PlainScene));
    exe_initScript(scene->script, transition);
    return scene;
}

static void *createJumpScene(char const *transition) {
    // TODO: stuff.
    return 0;
}

static void *createBoatScene(char const *transition) {
    // TODO: stuff.
    return 0;
}

static void *createAdventureScene(char const *transition) {
    // TODO: stuff.
    return 0;
}

static void plainFrame(struct SceneFrame *scene) {
    struct PlainScene *scene = 
}

struct Engine *game_createEngine(char const *transition) {
    struct Engine *engine = malloc(sizeof(struct Engine));
    engine->time = 0;
    engine->scenes = 0;
    game_transition(engine, transition);
    return engine;
}

void game_transition(struct Engine *engine, char const *transition) {
    log_info("Processing transition '%s'", transition);
    char action = transition[0];
    if (!action) return;
    char creation = transition[1];
    struct SceneFrame *scene = 0;
    if (creation) {
        scene = malloc(sizeof(struct SceneFrame));
        if (creation == 'p') scene->scene = createPlainScene(transition + 2);
        else if (creation == 'j') {
            scene->scene = createJumpScene(transition + 2);
        } else if (creation == 'b') { 
            scene->scene = createBoatScene(transition + 2);
        } else if (creation = 'a') {
            scene->scene = createAdventureScene(transition + 2);
        } else {
            log_error(
                "No such scene type as %c in transition '%s'",
                creation,
                transition
            );
        }
    }
    if (action == 'r') {
        struct SceneFrame *newFront = engine->scenes->next;
        free(engine->scenes);
        if (scene) {
            scene->next = newFront;
            engine->scenes = scene;
        } else {
            engine->scenes = newFront;
        }
    } else if (action == 'p') {
        if (scene) {
            scene->next = engine->scenes;
            engine->scenes = scene;
        } else {
            log_error(
                "Push transition without scene creation '%s'",
                transition
            );
        }
    } else {
        log_error("Unknown transition action '%c'", action);
    }
}

int game_frame(struct Engine *engine) {
    log_info("Frame %d", engine->time);
    struct SceneFrame *scene = engine->scenes;
    if (!scene) return 0;
    if (!scene->control) {
        switch (scene->type) {
        case SceneFrame_PLAIN:
            plainScene(scene);
            break;
        case SceneFrame_JUMP:
            jumpScene(scene);
            break;
        case SceneFrame_BOAT:
            boatScene(scene);
            break;
        case SceneFrame_ADVENTURE:
            adventureScene(scene);
            break;
        default:
            log_error("Unknown scene type %d", scene->type);
        }
    }
    // Increment the clock.
    engine->time++;
    return 1;
}

int game_handleInput(struct Engine *engine) {
    SDL_Event e;
    while(SDL_PollEvent(&e) != 0) {
        if(e.type == SDL_QUIT) return 0;
    }
    // TODO: handle other events.
    return 1;
}
