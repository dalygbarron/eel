#include "JumpScene.hh"






Actor *JumpScene::addActor(Actor *actor) {
    this->actors.push_front(actor);
}
