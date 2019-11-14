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
}

WalkScene::~WalkScene() {
    // does nothing atm.
}

sf::Vector2i WalkScene::sortMobs() {
    sf::Vector2i dirty(0, 0);
    // TODO: implement a nice adaptive sort. Timsort sounds easy.
    //       in the process of doing this sort we also need to check which mobs
    //       have got their dirty flag set and set the dirty region to reflect
    //       that too. Also, so we don't need to iterate over this shit twice,
    //       we can also set their dirty flag back to false again.
    return dirty;
}

void WalkScene::logic(float delta, sf::View &view) {
    // TODO: update walkstage.
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        this->camera.x -= delta * 400;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        this->camera.x += delta * 400;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        this->camera.y -= delta * 400;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        this->camera.y += delta * 400;
    }
    view.setCenter(this->camera);
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
