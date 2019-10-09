// TODO: find a better spot for this.
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#define LUA_USE_APICHECK

#include "static/Constant.hh"
#include "static/spdlog/spdlog.h"
#include "static/spdlog/rotating_file_sink.h"
#include "service/Game.hh"
#include "service/Config.hh"
#include "service/repository/TextRepository.hh"
#include "service/repository/TextureRepository.hh"
#include "service/repository/TilesetRepository.hh"
#include "service/repository/TileMapRepository.hh"
#include "service/repository/SoundRepository.hh"
#include "service/repository/MusicRepository.hh"
#include "service/Radio.hh"
#include "service/Engine.hh"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <forward_list>

#define DEFAULT_CONFIG_FILE "game.ini"

/**
 * Start of the program.
 * @param argc is the number of commandline arguments given.
 * @param argv is an array of commandline arguments as pointers to strings.
 * @return 0 when program exits expectedly, and otherwise returns something
 *         else probably meaningless.
 */
int main(int argc, char **argv) {
    // Start logging right away.
    spdlog::set_default_logger(
        spdlog::rotating_logger_mt("heart", "eel.log", 1048576, 2)
    );
    spdlog::flush_on(spdlog::level::debug); // TODO: change for prod
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
        // Instantiate the repositories.
        TextRepository textRepo(gameFile);
        TextureRepository textureRepo(gameFile);
        TilesetRepository tilesetRepo(gameFile, &textRepo, &textureRepo);
        TileMapRepository tileMapRepo(gameFile, &tilesetRepo);
        SoundRepository soundRepo(gameFile);
        MusicRepository musicRepo(gameFile);
        // Instantiate all the services.
        Config config(gameFile);
        ControlBuilder controlBuilder(&textureRepo, &config);
        Radio radio(&soundRepo, &musicRepo);
        Engine engine(
            &config,
            &textRepo,
            &textureRepo,
            &tilesetRepo,
            &tileMapRepo,
            &soundRepo,
            &musicRepo,
            &radio,
            0,
            &controlBuilder
        );
        Game game(&engine);
        // Make sure the engine version is compatible with the game.
        int engineMajor = config.getEngineMajor();
        int engineMinor = config.getEngineMinor();
        if (Constant::VERSION_MAJOR &&
            engineMajor != Constant::VERSION_MAJOR) {
            spdlog::critical("Game is for Eel version {}", engineMajor);
            throw -1;
        }
        if (Constant::VERSION_MINOR < engineMinor) {
            spdlog::critical(
                "Game requires at least Eel version {}.{}",
                engineMajor,
                engineMinor
            );
            throw -1;
        }
        // run the game.
        spdlog::info(
            "Starting '{}' version '{}'",
            config.getName(),
            config.getVersion()
        );
        int status = game.run();
        spdlog::info("Exiting Normally");
        return status;
    } catch(int e) {
        spdlog::warn("Aborting {}", e);
        return -1;
    }
}
