#ifndef TEXTURE_H
#define TEXTURE_H

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>

/**
 * A picture texture which is applied to a face.
 */
class Texture {
    unsigned int textureId;
    int width;
    int height;

public:
    /**
     * Creates an empty texture object with no image data inside.
     */
    Texture();

    /**
     * Destroys the texture object and whatever it currently contains.
     */
    ~Texture();

    /**
     * Loads a texture out of some pixel data.
     * @param pixels is the array of pixels each stored as 32 bit colour.
     * @param width  is the width of the image in the pixel array.
     * @param height is the height of the image in the pixel array.
     * @return true if successful and false otherwise.
     */
    int loadFromPixels(GLuint *pixels, int width, int height);

    /**
     * Deletes the data in the texture.
     */
    void free();

    /**
     * Renders the texture into the screen.
     * @param x is the horizontal position to place the texture.
     * @param y is the vertical position to place it.
     */
    void render(GLfloat x, GLfloat y);

    /**
     * Gives the texture's current ID on the GPU.
     * @return the id.
     */
    GLuint getTextureId();

    /**
     * gives you the texture's width.
     * @return the width.
     */
    unsigned int getWidth();

    /**
     * Gives you the texture's height.
     * @return the height.
     */
    unsigned int getHeight();
};

#endif
