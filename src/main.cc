// TODO: find a better spot for this.
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#define LUA_USE_APICHECK

#include "static/Constant.hh"
#include "static/spdlog/spdlog.h"
#include "static/spdlog/rotating_file_sink.h"
#include "service/Game.hh"
#include "service/Config.hh"
#include "service/Repository.hh"
#include "service/Radio.hh"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <forward_list>

#define DEFAULT_CONFIG_FILE "game.ini"

/**
 * Start of the program.
 * @param argc is the number of commandline arguments given.
 * @param argv is an array of commandline arguments as pointers to strings.
 * @return 0 when program exits expectedly, and otherwise returns something else probably meaningless.
 */
int main(int argc, char **argv) {
    // Start logging right away.
    spdlog::set_default_logger(spdlog::rotating_logger_mt("heart", "eel.log", 1048576, 2));
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
        ControlBuilder controlBuilder(&repository, &config);
        Timer timer;
        Radio radio(&repository);
        Game game(&config, &repository, &controlBuilder, &timer, &radio);
        // run the game.
        spdlog::info("Starting '{}' version '{}'", config.get("title"), config.get("version"));
        int status = game.run();
        spdlog::info("Exiting Normally");
        return status;
    } catch(...) {
        spdlog::warn("Aborting");
        return -1;
    }
}
