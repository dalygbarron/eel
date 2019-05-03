#ifndef TEXTURE_H
#define TEXTURE_H

#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include "Vector.hh"

/**
 * A picture texture which is applied to a face.
 * All the fields of this type are publically accessible, so if you want to stop them from being modified you must pass
 * the object as a const.
 */
class Texture {
    /**
     * Gets the nearest power of two.
     * @param num is the number we are trying to be close to.
     */
    int powerOfTwo(int num);

    /**
     * Initialises the texture's vertex buffer object.
     */
    void initVbo();

    /**
     * Frees the texture's vertex buffer object.
     */
    void freeVbo();

public:
    unsigned int textureId = 0;
    unsigned int vboId = 0;
    unsigned int iboId = 0;
    Vector2 textureSize;
    Vector2 imageSize;

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
     * @param size   is the size of the array of data.
     * @return true if successful and false otherwise.
     */
    int loadFromPixels(GLuint *pixels, Vector2 size);

    /**
     * Deletes the data in the texture.
     */
    void freeTexture();

    /**
     * Renders the texture into the screen.
     * @param pos  is the place to render it.
     * @param clip is the rectangle to fit it into.
     */
    void render(Vector2 pos, Rect2 clip);

    /**
     * gives you the texture's dimensions.
     * @return the size.
     */
    Vector2 getSize();
};

#endif
