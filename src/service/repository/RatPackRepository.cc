#include "service/repository/RatPackRepository.hh"
#include "static/Utils.hh"

RatPackRepository::RatPackRepository(
    char const &root,
    TextRepository const &textRepo,
    Repository<sf::Texture> &textureRepo
):
    Repository(root),
    textRepo(textRepo),
    textureRepo(textureRepo)
{
    // doesn't anything now.
}

RatPack *RatPackRepository::create(char const &name, char const &key) const {
    spdlog::info("Creating rat pack: '{}'", &name);
    pugi::xml_document doc;
    pugi::xml_node node = Utils::openXml(
        doc,
        *"pack",
        this->textRepo.get(key).get()
    );
    Path imagePath(key, *node.attribute("image").value());
    sf::Texture &texture = this->textureRepo.snatch(imagePath.get());
    RatPack *ratPack = new RatPack(texture);
    for (pugi::xml_node rat = node.child("rat"); rat;
        rat = rat.next_sibling("rat")
    ) {
        ratPack->addRat(*rat.attribute("name").value(), sf::FloatRect(
            rat.attribute("x").as_int(),
            rat.attribute("y").as_int(),
            rat.attribute("w").as_int(),
            rat.attribute("h").as_int()
        ));
    }
    return ratPack;
}
