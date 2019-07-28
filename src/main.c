/**
 * Starting point of the engine, is used to call other startup functionality
 * before moving into the scene stack.
 */

#include "src/log.h"
#include "src/const.h"
#include "src/render.h"
#include "src/game.h"
#include "src/model/Display.h"
#include <stdio.h>

int main(int argc, char const **argv) {
    // Tell the world we are starting up.
    log_info(
        "Eel engine version %d.%d.%d starting",
        const_V_MAJOR,
        const_V_MINOR,
        const_V_REVISION
    );
    // Start up the game bits.
    struct Display *display = render_createDisplay(640, 480, "Eel");
    struct Engine *engine = game_createEngine("pp");
    // main loop
    while (engine->scenes) {
        if (!game_handleInput(engine)) break;
        game_frame(engine);
        render_frame(engine, display);
    }
    // cleaning up.
    return 0;
}
