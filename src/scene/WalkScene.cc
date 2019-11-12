#include "scene/WalkScene.hh"

WalkScene::WalkScene(
    Engine const &engine,
    WalkStage const &prototype
):
    Scene(engine),
    stage(prototype)
{
    sf::FloatRect offset = engine.joinRatPack(
        engine.config.getOption(*Config::OPTION_SPRITESHEET),
        engine.config.getOption(*Config::OPTION_TILESET_SLOT),
        prototype.tileset.get().texture.get()
    );
    if (offset.left > 0 || offset.top > 0) {
        spdlog::warn("Offset of tileset in spritesheet not zero");
    }
    engine.paneBuffer.sortMode = SORT_Y;
    engine.paneBuffer.clear();
    std::vector<Slice const *> &slices = this->stage.getSlices(
        sf::Vector2i(0, 0)
    );
    for (Slice const *slice: slices) {
        int n = slice->size.x * slice->size.y;
        for (int i = 0; i < n; i++) {
            this->walkStage.addTile(slice->data[i], sf::Vector3f(
                i % slice->size.x,
                i / slice->size.x,
                slice->height
            ));
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

void WalkScene::logic(float delta) {
    // TODO: update walkstage.
}

void WalkScene::draw(
    sf::RenderTarget &target,
    sf::RenderStates states
) const {
    target.draw(this->stage, states);
}
