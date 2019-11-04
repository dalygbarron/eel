#include "service/repository/WalkStageRepository.hh"
#include "static/spdlog/spdlog.h"
#include <SFML/Graphics.hpp>

WalkStageRepository::WalkStageRepository(
    char const &root,
    Repository<char> const &textRepo,
    Repository<Tileset> const &tilesetRepo
):
    Repository(root),
    textRepo(textRepo),
    tilesetRepo(tilesetRepo)
{
    // yeeeet.
}

WalkStage *WalkStageRepository::create(
    char const &filename,
    char const &key
) const {
    spdlog::info("creating walkstage: '{}'", &filename);
    pugi::xml_document doc;
    pugi::xml_node node = Utils::openXml(
        doc,
        *"map",
        this->textRepo.get(key).get()
    );
    sf::Color bg(strtol(node.attribute("backgroundcolor").value() + 1, 0 ,16));
    sf::Vector2u tileSize;
    sf::Vector2u chunkSize(0, 0);
    tileSize.x = node.attribute("tilewidth").as_int();
    tileSize.y = node.attribute("tileheight").as_int();
    pugi::xml_node tilesetNode = node.child("tileset");
    if (!tilesetNode) {
        spdlog::error("Couldn't find tileset node");
        return 0;
    }
    Path tilesetPath(key, *tilesetNode.attribute("source").value());
    Asset<Tileset> const &tileset = this->tilesetRepo.get(tilesetPath.get());
    WalkStage *walkStage = new WalkStage(bg, tileset, chunkSize, tileSize);
    return walkStage;
}
