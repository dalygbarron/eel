#include <iostream>
#include <fstream>
#include <forward_list>
#include <SFML/Graphics.hpp>

// TODO: find a better spot for this.
//#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG

#include "spdlog/spdlog.h"
#include "spdlog/daily_file_sink.h"

/**
 * Start of the program.
 * @param argc is the number of commandline arguments given.
 * @param argv is an array of commandline arguments as pointers to strings.
 * @return 0 when program exits expectedly, and otherwise returns something else probably meaningless.
 */
int main(int argc, char **argv) {
    // Start logging right away.
    spdlog::set_default_logger(spdlog::daily_logger_mt("heart", "logs/piss2.log", 2, 30));
    spdlog::flush_on(spdlog::level::debug); // TODO: obviously change this for production to error.
    spdlog::flush_every(std::chrono::seconds(10));
    spdlog::info("Game Commencing Normally");
    // Get the game file
    char const *gameFile;
    if (argc == 2) gameFile = argv[1];
    else gameFile = Config::DEFAULT_GAME_FILE;
    // Start up the game systems.
    Config config(gameFile);
    Repository repository(&config);
    BulletManager bulletManager(&config, &repository);
    Game game(&config, &repository);
    // run the game.
    int status = game.run();
    // all over.
    spdlog::info("Game Ending Normally");
    return status;
}
