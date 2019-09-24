#include "scene/WalkScene.hh"

WalkScene::WalkScene(Engine const *engine, char const *level): Scene(engine) {
    this->map = engine->repository->getTileMap(level);
    this->buffer.setPrimitiveType(sf::Quads);
    this->buffer.setUsage(sf::VertexBuffer::Usage::Stream);
    this->buffer.create(WalkScene::MAX_MOBS * 4);
}

WalkScene::~WalkScene() {
    // TODO: delete junk.
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
    // Update objects that need to be updated.
    for (int i = 0; i < nActors; i++) {
        // TODO: update actors.
    }
    for (int i = 0; i < nBullets; i++) {
        // TODO: update bullets.
    }
    // Sort all mobs and upload dirty to GPU.
    sf::Vector2i dirty = this->sortMobs();
    for (int i = dirty.x; i < dirty.y; i++) {
        this->mobs[i]->moveTo(this->vertices + i * 4);
    }
    this->buffer.update(
        this->vertices + dirty.x * 4,
        (dirty.y - dirty.x) * 4,
        dirty.x * 4
    );
}

void WalkScene::render(
    sf::RenderTarget *target,
    sf::RenderStates states
) const {
    target->draw(this->buffer);
}
