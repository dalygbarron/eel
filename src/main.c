#include "log.h"
#include "const.h"
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
    return 0;
}
