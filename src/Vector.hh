#ifndef VECTOR_2_H
#define VECTOR_2_H

/**
 * A point in 2d space.
 */
class Vector2 {
public:
    float x;
    float y;

    /**
     * Creates a point at the origin.
     */
    Vector2();

    /**
     * Creates a vector and sets it's properties.
     * @param x is it's horizontal position.
     * @param y is it's vertical position.
     */
    Vector2(float x, float y);

    // TODO: operator overloading.
};

/**
 * A rectangle in 2d space.
 */
class Rect2 {
public:
    Vector2 pos;
    Vector2 size;

    /**
     * Creates a rectangle of no size at the origin.
     */
    Rect2();

    /**
     * Creates a nice rectangle.
     * @param pos is the top left corner of the rectangle's position.
     * @param size is the width and height of the rectangle.
     */
    Rect2(Vector2 pos, Vector2 size);

    /**
     * Creates a nice rectangle from all floats.
     * @param x is the left position.
     * @param y is the top position.
     * @param w is the width.
     * @param h is the height.
     */
    Rect2(float x, float y, float w, float h);

    // TODO: operator overloading.
}

#endif
