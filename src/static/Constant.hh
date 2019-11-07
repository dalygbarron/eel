#ifndef CONSTANT_H
#define CONSTANT_H

/**
 * Namespace that provides values that are constant for the compiled
 * application and are too general to belong in a single other place.
 */
namespace Constant {
    // Versions.
    constexpr static int const VERSION_MAJOR = 0;
    constexpr static int const VERSION_MINOR = 1;
    constexpr static int const VERSION_REVISION = 0;
    // Engine constant values.
    constexpr static float const FPS_WARN = 55;
    constexpr static float const PI = 3.14159;
    constexpr static int const FILENAME_BUFFER_SIZE = 128;
    constexpr static int const SMALL_TEXT_BUFFER_SIZE = 256;
    constexpr static int const TRANSITION_BUFFER_SIZE = 1024;
    constexpr static int const TILESET_MAX_WIDTH = 512;
    constexpr static int const TILESET_MAX_HEIGHT = 1536;
    constexpr static char const *SCRIPT_ENTRY = "main";
    constexpr static int MAX_PANES = 4096;
};

#endif
