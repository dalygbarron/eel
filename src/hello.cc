#include <iostream>
#include <ctime>
#include "Script.hh"
#include "Graphics.hh"
#include "Audio.hh"
#include "Input.hh"
#include "Texture.hh"
#include "Vector.hh"
#include "BulletManager.hh"
#include "Shader.hh"
#include "PolygonShader.hh"
#include <SDL2/SDL.h>

int main(int argc, char** argv) {
    Graphics::init("game", argc > 1);
    Audio::init();
    //Audio::play("test/song/rorsh.ogg");
    srand(time(0));
    PolygonShader *shader = new PolygonShader();
    shader->load();
    Texture *a = Graphics::loadTextureFile("test/image/cirno.png");
    Texture *b = Graphics::loadTextureFile("test/image/flan.png");

    BulletManager *bullets = new BulletManager(b);



    int frame = 0;
    int oldTime = SDL_GetTicks();
    int timer = 0;
    while (true) {
        if (!Input::process()) break;
        frame++;
        int newTime = SDL_GetTicks();
        timer += newTime - oldTime;
        oldTime = newTime;
        if (timer >= 1000) {
            timer -= 1000;
            std::cout << frame << std::endl;
            frame = 0;
        }
        bullets->process();

        Graphics::clear();
        glLoadIdentity();
        shader->bind();
        shader->update(newTime / 1000.0);
        a->render(Vector2(640, 480), Rect2());
        shader->unbind();
        bullets->render();
        Graphics::flip();
    }
    delete a;
    delete b;
    Graphics::close();
    Audio::close();
    return 0;
}
