#include "service/repository/RatPackRepository.hh"

RatPackRepository::RatPackRepository(
    char const *root,
    TextRepository const *textRepo,
    Repository<sf::Texture> *textureRepo
): Repository(root) {
    this->textRepo = textRepo;
    this->textureRepo = textureRepo;
}

RatPack *RatPackRepository::create(char const *name, char const *key) const {
    pugi::xml_node node = this->textRepo->getXml(key, "pack");
    Path imagePath(key, node.attribute("image").value());
    sf::Texture *texture = this->textureRepo->snatch(imagePath.get());
    RatPack *ratPack = new RatPack(texture);
    for (pugi::xml_node rat = node.child("rat"); rat;
        rat = rat.next_sibling("rat")
    ) {
        ratPack->addRat(rat.attribute("name").value(), sf::IntRect(
            rat.attribute("x").as_int(),
            rat.attribute("y").as_int(),
            rat.attribute("w").as_int(),
            rat.attribute("h").as_int()
        ));
    }
    return ratPack;
}
