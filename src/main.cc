#include "Constant.hh"
#include "Game.hh"
#include "Config.hh"
#include "Repository.hh"
#include "BulletManager.hh"
#include <iostream>
#include <fstream>
#include <forward_list>
#include <SFML/Graphics.hpp>

// TODO: find a better spot for this.
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG

#include "spdlog/spdlog.h"
#include "spdlog/daily_file_sink.h"

#define DEFAULT_CONFIG_FILE "game.ini"

/**
 * Start of the program.
 * @param argc is the number of commandline arguments given.
 * @param argv is an array of commandline arguments as pointers to strings.
 * @return 0 when program exits expectedly, and otherwise returns something else probably meaningless.
 */
int main(int argc, char **argv) {
    // Start logging right away.
    spdlog::set_default_logger(spdlog::daily_logger_mt("heart", "logs/eel.log", 2, 30));
    spdlog::flush_on(spdlog::level::debug); // TODO: obviously change this for production to error.
    spdlog::flush_every(std::chrono::seconds(10));
    spdlog::info(
        "Eel Version {}.{}.{}",
        Constant::VERSION_MAJOR,
        Constant::VERSION_MINOR,
        Constant::VERSION_REVISION
    );
    // Get the game file
    char const *gameFile;
    if (argc == 2) gameFile = argv[1];
    else gameFile = DEFAULT_CONFIG_FILE;
    // Start up the game systems.
    try {
        Config config(gameFile);
        Repository repository(&config);
        BulletManager bulletManager(&config, &repository);
        Game game(&config, &repository, &bulletManager);
        // run the game.
        spdlog::info("Starting '{}' version '{}'", config.get("title"), config.get("version"));
        int status = game.run();
        spdlog::info("Exiting Normally");
        return status;
    } catch(...) {
        spdlog::info("Aborting");
        return -1;
    }
}
