#ifndef VECTOR_2_H
#define VECTOR_2_H

/**
 * A point in continuous 2d space.
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

    /**
     * Tells you if either dimension is non zero.
     * @return true if so and false if not.
     */
    int exists() const;

    /**
     * Gives the area of a rectangle with the origin and (x, y) at opposing corners.
     * @return the area which is x * y but non negative.
     */
    float area() const;

    /**
     * Gives the length of the line from the origin to the point (x, y).
     * @return the length.
     */
    float length() const;

    /**
     * Gives the x component as an integer.
     * @return the x component of the vector as an integer.
     */
    int iX() const;

    /**
     * Gives the y component as an integer.
     * @return the y component of the vector as an integer.
     */
    int iY() const;

    /**
     * Addition operator.
     * @param other is the other position to add on to this one.
     * @return the new position.
     */
    Vector2 operator+(Vector2 other) const;

    /**
     * Subtraction operator.
     * @param other is the other position to remove from this one.
     * @return the new position.
     */
    Vector2 operator-(Vector2 other) const;

    /**
     * Multiplication operator.
     * @param other is the other position to multiply this one by.
     * @return the new position.
     */
    Vector2 operator*(Vector2 other) const;

    /**
     * Division operator.
     * @param other is the other position to divide this one by.
     * @return the new position.
     */
    Vector2 operator/(Vector2 other) const;

    /**
     * Addition assignment operator.
     * @param other is the other position to add to this one.
     * @return this I guess.
     */
    Vector2 operator+=(Vector2 other);

    /**
     * Multiplication operator with float.
     * @param other is the other position to multiply this one by.
     * @return the new position.
     */
    Vector2 operator*(float other) const;

    /**
     * Division operator with float.
     * @param other is the other position to divide this one by.
     * @return the new position.
     */
    Vector2 operator/(float other) const;
};

/**
 * A three dimensional value.
 */
class Vector3 {
public:
    float x;
    float y;
    float z;

    /**
     * Makes a vector with all zeroes.
     */
    Vector3();

    /**
     * Creates a vector 3.
     * @param x is the first component.
     * @param y is the second component.
     * @param z is the third component.
     */
    Vector3(float x, float y, float z);
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

    /**
     * Gives the position of the bottom right corner of the rectangle so pos + size basically.
     * @return the position of the bottom right corner.
     */
    Vector2 end() const;

    // TODO: operator overloading.
};

#endif
