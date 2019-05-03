#include <iostream>
#include <ctime>
#include "Script.hh"
#include "Graphics.hh"
#include "Input.hh"
#include "Texture.hh"
#include "Vector.hh"
#include "BulletManager.hh"
#include "Shader.hh"
#include "PolygonShader.hh"
#include <SDL2/SDL.h>

#define N_BULLETS 1024

int main(int argc, char** argv) {
    Graphics::init("game", argc > 1);
    srand(time(0));
    Shader *shader = new PolygonShader();
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
        a->render(Vector2(0, 0), Rect2());
        shader->unbind();
        bullets->render();
        Graphics::flip();
    }
    delete a;
    delete b;
    Graphics::close();
    return 0;
}
