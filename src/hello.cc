#include <iostream>
#include "Script.hh"
#include "Graphics.hh"
#include "Input.hh"
#include "Texture.hh"

int main(int argc, char** argv) {
    Graphics::init("game");
    Texture *texture = Graphics::createTexture(512, 512);
    while (true) {
        if (!Input::process()) break;
        Graphics::clear();
        texture->render(256, 0);
        Graphics::flip();
    }
    delete texture;
    Graphics::close();
    return 0;
}
