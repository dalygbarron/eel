#include "scene/WalkScene.hh"
#include <SFML/Window.hpp>

WalkScene::WalkScene(
    Engine const &engine,
    WalkStage const &prototype
):
    Scene(engine),
    stage(prototype),
    camera(0, 0)
{
    sf::FloatRect offset = engine.joinRatPack(
        engine.config.getOption(*Config::OPTION_SPRITESHEET),
        engine.config.getOption(*Config::OPTION_TILESET_SLOT),
        prototype.tileset.get().texture.get()
    );
    if (offset.left > 0 || offset.top > 0) {
        spdlog::warn("Offset of tileset in spritesheet not zero");
    }
    engine.paneBuffer.clear();
    this->stage.attach(engine.paneBuffer);
    // Add some tiles.
    for (int x = -10; x < 20; x++) {
        for (int y = -10; y < 20; y++) {
            std::vector<Slice const *> const *slices = this->stage.getSlices(
                sf::Vector2i(x, y)
            );
            if (!slices) continue;
            for (Slice const *slice: *slices) {
                spdlog::info(
                    "adding slice {} {} {} {} {}",
                    slice->size.x,
                    slice->size.y,
                    slice->height,
                    x,
                    y
                );
                int n = slice->size.x * slice->size.y;
                for (int i = 0; i < n; i++) {
                    if (slice->data[i]) {
                        this->stage.addTile(slice->data[i], sf::Vector3f(
                            i % slice->size.x + x,
                            i / slice->size.x + y,
                            slice->height
                        ));
                    }
                }
            }
        }
    }
    // Add the player.
    Persona proto;
    this->player = this->stage.addActor(proto, sf::Vector3f(0, 0, 3));
}

WalkScene::~WalkScene() {
    // does nothing atm.
}

void WalkScene::logic(float delta, sf::View &view) {
    this->stage.update(delta);
    if (this->player) {
        view.setCenter(Utils::screenPosition(this->player->position));
    }
}

void WalkScene::draw(
    sf::RenderTarget &target,
    sf::RenderStates states
) const {
    target.draw(this->stage, states);
    this->engine.paneBuffer.render(
        target, 
        this->engine.getRatPackRepository().get(this->engine.config.getOption(*Config::OPTION_SPRITESHEET)).get().getTexture()
    );
}
