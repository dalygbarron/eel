#include "BulletManager.hh"

#include <cstdlib>
#include <cstddef>
#include <cmath>
#include <OpenGL/gl.h>
#include "Graphics.hh"
#include "Vector.hh"

BulletManager::BulletManager(Texture const *texture) {
    this->texture = texture;
    for (int i = 0; i < BulletManager::MAX_BULLETS; i++) {
        this->bullets[i].colour.x = (rand() % 20) / (float)20;
        this->bullets[i].colour.y = (rand() % 20) / (float)20;
        this->bullets[i].colour.z = (rand() % 20) / (float)20;

        this->bullets[i].pos.x = rand() % Graphics::WIDTH / 2 + Graphics::WIDTH / 4;
        this->bullets[i].pos.y = rand() % Graphics::HEIGHT;
        int angle = rand();
        this->bullets[i].velocity.y = 0.1;
        angle = rand();
        this->bullets[i].gravity.x = cos(angle) / 9000;
        this->bullets[i].gravity.y = sin(angle) / 9000;
    }
}

void BulletManager::process() {
    for (int i = 0; i < BulletManager::MAX_BULLETS; i++) {
        this->bullets[i].pos += this->bullets[i].velocity;
        this->bullets[i].velocity += this->bullets[i].gravity;
        if (this->bullets[i].pos.y > Graphics::HEIGHT) this->bullets[i].pos.y -= Graphics::HEIGHT;
        if (this->bullets[i].pos.x > Graphics::WIDTH / 4 * 3) this->bullets[i].pos.x -= Graphics::WIDTH / 2;
        if (this->bullets[i].pos.y < 0) this->bullets[i].pos.y += Graphics::HEIGHT;
        if (this->bullets[i].pos.x < Graphics::WIDTH / 4) this->bullets[i].pos.x += Graphics::WIDTH / 2;
    }
}

void BulletManager::render() {
    Rect2 textureRect(Vector2(), this->texture->imageSize / this->texture->textureSize);
    Vector2 quad = this->texture->imageSize;
    // set up gl
    glBindTexture(GL_TEXTURE_2D, this->texture->textureId);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    Rect2 vertex[4];
    vertex[0].pos = textureRect.pos;
    vertex[1].pos = textureRect.pos + Vector2(textureRect.size.x, 0);
    vertex[2].pos = textureRect.end();
    vertex[3].pos = textureRect.pos + Vector2(0, textureRect.size.y);
    vertex[0].size = Vector2();
    vertex[1].size = Vector2(quad.x, 0);
    vertex[2].size = quad;
    vertex[3].size = Vector2(0, quad.y);
    glBindBuffer(GL_ARRAY_BUFFER, this->texture->vboId);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(Rect2), vertex);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Rect2), (GLvoid*)offsetof(Rect2, pos));
    glVertexPointer(2, GL_FLOAT, sizeof(Rect2), (GLvoid*)offsetof(Rect2, size));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->texture->iboId);
    // unique part.
    for (int i = 0; i < BulletManager::MAX_BULLETS; i++) {
        glLoadIdentity();
        glTranslatef(this->bullets[i].pos.x, this->bullets[i].pos.y, 0);
        glColor3f(this->bullets[i].colour.x ,this->bullets[i].colour.y,this->bullets[i].colour.z);
        glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
    }
    // finish off.
    glColor3f(1, 1, 1);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}
