#ifndef CONFIG_H
#define CONFIG_H

// values
#define FPS 60.0
#define FPS_WARN 55.0
#define BULLET_LIMIT 2048
#define FILENAME_BUFFER_SIZE 64
#define PI 3.14159

// filenames
#define DEFAULT_GAME_FILE "game.ini"
#define BULLET_FILE "bullets"
#define FISH_FILE "fishes"

// macros
#define PPS(n) (n / FPS)

#endif
