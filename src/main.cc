// TODO: find a better spot for this.
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG
#define LUA_USE_APICHECK

#include "static/Constant.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include "static/spdlog/rotating_file_sink.h"
#include "service/Game.hh"
#include "service/Config.hh"
#include "service/repository/TextRepository.hh"
#include "service/repository/TextureRepository.hh"
#include "service/repository/TilesetRepository.hh"
#include "service/repository/SoundRepository.hh"
#include "service/repository/RatPackRepository.hh"
#include "service/repository/WalkStageRepository.hh"
#include "service/Radio.hh"
#include "service/Engine.hh"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <forward_list>

#define DEFAULT_CONFIG_FILE "game.ini"

/**
 * Logs some basic information.
 */
void diagnostics() {
    spdlog::info(
        "Eel Version {}.{}.{}",
        Constant::VERSION_MAJOR,
        Constant::VERSION_MINOR,
        Constant::VERSION_REVISION
    );
    spdlog::info(
        "Largest allowed texture on given hardware is {}",
        sf::Texture::getMaximumSize()
    );
}

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
    diagnostics();
    // Get the game file
    char const *gameFile;
    if (argc == 2) gameFile = argv[1];
    else gameFile = DEFAULT_CONFIG_FILE;
    // Start up the game systems.
    try {
        // Instantiate the repositories and then the services.
        TextRepository textRepo(*gameFile);
        TextureRepository textureRepo(*gameFile);
        TilesetRepository tilesetRepo(*gameFile, textRepo, textureRepo);
        SoundRepository soundRepo(*gameFile);
        RatPackRepository ratPackRepo(*gameFile, textRepo, textureRepo);
        WalkStageRepository walkStageRepo(*gameFile, textRepo, tilesetRepo);
        // Load the config object.
        // TODO: this is a bit long for the middle of the main function, also
        //       that xml document is going to be in memory for the entire game
        //       which is a bit unnecessary.
        pugi::xml_document doc;
        pugi::xml_node gameNode = Utils::openXml(
            doc,
            *"game",
            textRepo.get(*"game.xml").get()
        );
        Config config(
            *gameNode.attribute("name").value(),
            *gameNode.attribute("version").value(),
            gameNode.attribute("engineMajor").as_int(),
            gameNode.attribute("engineMinor").as_int(),
            gameNode.attribute("width").as_int(),
            gameNode.attribute("height").as_int()
        );
        pugi::xml_node opts = gameNode.child("opts");
        if (opts) {
            for (pugi::xml_node opt = opts.child("opt"); opt; 
                opt = opt.next_sibling("opt")) {
                config.addOption(
                    *opt.attribute("name").value(),
                    *opt.attribute("value").value()
                );
            }
        }
        // Make services
        ControlBuilder controlBuilder(textureRepo, config);
        Radio radio(soundRepo);
        Status status;
        // Create the engine and game objects.
        Engine engine(
            *gameFile,
            config,
            textRepo,
            textureRepo,
            tilesetRepo,
            soundRepo,
            ratPackRepo,
            walkStageRepo,
            radio,
            status,
            controlBuilder
        );
        Game game(engine);
        // Make sure the engine version is compatible with the game.
        if (Constant::VERSION_MAJOR &&
            config.engineMajor != Constant::VERSION_MAJOR) {
            spdlog::critical("Game is for Eel version {}", config.engineMajor);
            throw -1;
        }
        if (Constant::VERSION_MINOR < config.engineMinor) {
            spdlog::critical(
                "Game requires at least Eel version {}.{}",
                config.engineMajor,
                config.engineMinor
            );
            throw -1;
        }
        // run the game.
        spdlog::info(
            "Starting '{}' version '{}'",
            config.name,
            config.version
        );
        int result = game.run();
        spdlog::info("Exiting Normally: {}", result);
        return result;
    } catch (std::exception e) {
        spdlog::warn("Aborting with uncaught exception '{}'", e.what());
        return -1;
    } catch (int e) {
        spdlog::warn("Aborting with uncaught exception#{}", e);
        return e;
    }
}
