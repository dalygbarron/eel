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
    // Layers.
    for (
        pugi::xml_node layer = node.child("layer");
        layer;
        layer = layer.next_sibling("layer")
    ) {
        pugi::xml_node data = layer.child("data");
        int height = 0;
        if (!data) continue;
        if (strcmp(data.attribute("encoding").value(), "base64") != 0) {
            spdlog::warn("can only parse tiled layer data in base64 encoding");
            continue;
        }
        for (
            pugi::xml_node chunk = data.child("chunk");
            chunk;
            chunk = chunk.next_sibling("chunk")
        ) {
            sf::Vector2i pos;
            sf::Vector2u size;
            pos.x = chunk.attribute("x").as_int();
            pos.y = chunk.attribute("y").as_int();
            size.x = chunk.attribute("width").as_int();
            size.y = chunk.attribute("height").as_int();
            pugi::xml_text text = chunk.text();
            if (!text) {
                spdlog::warn("Chunk has size but not content");
                continue;
            }
            unsigned char buffer[size.x * size.y * 4];
            Utils::parseBase64String(
                *text.get(),
                buffer[0],
                size.x * size.y * 4
            );
            Slice *slice = new Slice(height, size);
            for (int i = 0; i < size.x * size.y; i++) {
                slice->data[i] = buffer[i * 4];
            }
            walkStage->addSlice(pos, *slice);
        }
    }
    return walkStage;
}
