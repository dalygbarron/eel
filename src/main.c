#include "log.h"
#include "const.h"
#include <stdio.h>

int main(int argc, char const **argv) {
    log_info("Eel engine version %d.%d.%d starting", const_V_MAJOR, const_V_MINOR, const_V_REVISION);
    return 0;
}
