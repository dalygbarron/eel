#include "Texture.hh"

#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <OpenGL/gl.h>
#include "Vector.hh"


Texture::Texture() {
    // does nothing.
}

Texture::~Texture() {
    this->freeTexture();
    this->freeVbo();
}

int Texture::loadFromPixels(GLuint *pixels, Vector2 size) {
    this->freeTexture();
    this->textureSize = size;
    this->imageSize = size;
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.iX(), size.iY(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    // Check for errors.
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "error loading texture: " << error << std::endl;
        return false;
    }
    // generate vbo
    this->initVbo();
    return true;
}

void Texture::freeTexture() {
    if (this->textureId != 0) {
        glDeleteTextures(1, &this->textureId);
        this->textureId = 0;
    }
    this->textureSize = Vector2();
    this->imageSize = Vector2();
}

void Texture::render(Vector2 pos, Rect2 clip) {
    if (this->textureId == 0) return;
    // setting up the right stuff.
    Rect2 textureRect(Vector2(), this->imageSize / this->textureSize);
    Rect2 quad(this->imageSize * -0.5, this->imageSize);
    if (clip.size.exists()) {
        // TODO: this is probably screwed.
        textureRect.pos = clip.pos / this->textureSize;
        textureRect.size = clip.end() / this->textureSize;
        quad = Rect2(Vector2(), clip.size);
    }
    // set up data to send
    glTranslatef(pos.x, pos.y, 0);
    Rect2 vertex[4];
    vertex[0].pos = textureRect.pos;
    vertex[1].pos = textureRect.pos + Vector2(textureRect.size.x, 0);
    vertex[2].pos = textureRect.end();
    vertex[3].pos = textureRect.pos + Vector2(0, textureRect.size.y);
    vertex[0].size = quad.pos;
    vertex[1].size = quad.pos + Vector2(quad.size.x, 0);
    vertex[2].size = quad.end();
    vertex[3].size = quad.pos + Vector2(0, quad.size.y);
    // binding and rendering.
    glBindTexture(GL_TEXTURE_2D, this->textureId);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboId);
    glBufferSubData(GL_ARRAY_BUFFER, 0, 4 * sizeof(Rect2), vertex);
    glTexCoordPointer(2, GL_FLOAT, sizeof(Rect2), (GLvoid*)offsetof(Rect2, pos));
    glVertexPointer(2, GL_FLOAT, sizeof(Rect2), (GLvoid*)offsetof(Rect2, size));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iboId);
    glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, 0);
    // finish off.
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}

int Texture::powerOfTwo(int num) {
    if (num != 0) {
        num--;
        num |= (num >> 1);
        num |= (num >> 2);
        num |= (num >> 4);
        num |= (num >> 8);
        num |= (num >> 16);
        num++;
    }
    return num;
}

void Texture::initVbo() {
    if (!this->textureId || this->vboId || this->iboId) return;
    Rect2 vertex[4];
    GLuint index[4];
    // fill index data.
    index[0] = 0;
    index[1] = 1;
    index[2] = 2;
    index[3] = 3;
    // create vbo.
    glGenBuffers(1, &this->vboId);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboId);
    glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(Rect2), vertex, GL_DYNAMIC_DRAW);
    //create ibo.
    glGenBuffers(1, &this->iboId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->iboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), index, GL_DYNAMIC_DRAW);
    // unbind buffers.
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Texture::freeVbo() {
    if (!this->vboId) return;
    glDeleteBuffers(1, &this->vboId);
    glDeleteBuffers(1, &this->iboId);
}
