/**
 * Starting point of the engine, is used to call other startup functionality
 * before moving into the scene stack.
 */

#include "src/log.h"
#include "src/const.h"
#include "src/render.h"
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
    // Start up the game window.
    struct Display = render_createDisplay("Eel", 640, 480);
    return 0;
}
