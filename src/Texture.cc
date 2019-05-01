#include "Texture.hh"

#define GL_SILENCE_DEPRECATION
#include <iostream>
#include <OpenGL/gl.h>

Texture::Texture() {
    this->textureId = 0;
    this->width = 0;
    this->height = 0;
}

Texture::~Texture() {
    this->free();
}

int Texture::loadFromPixels(GLuint *pixels, int width, int height) {
    this->free();
    this->width = width;
    this->height = height;
    glGenTextures(1, &this->textureId);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
    // Check for errors.
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "error loading texture: " << error << std::endl;
        return false;
    }
    return true;
}

void Texture::free() {
    if (this->textureId != 0) {
        glDeleteTextures(1, &this->textureId);
        this->textureId = 0;
    }
    this->width = 0;
    this->height = 0;
}

void Texture::render(GLfloat x, GLfloat y) {
    if (this->textureId == 0) return;
    glLoadIdentity();
    glTranslatef(x, y, 0);
    glBindTexture(GL_TEXTURE_2D, this->textureId);
    // TODO: this is slow and shitty. We can send this data to the gpu apparantly.
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex2f(0, 0);
    glTexCoord2f(1, 0);
    glVertex2f(this->width, 0);
    glTexCoord2f(1, 1);
    glVertex2f(this->width, this->height);
    glTexCoord2f(0, 1);
    glVertex2f(0, this->height);
    glEnd();

}

GLuint Texture::getTextureId() {
    return this->textureId;
}

unsigned int Texture::getWidth() {
    return this->width;
}

unsigned int Texture::getHeight() {
    return this->height;
}
