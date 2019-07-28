#ifndef UTIL_H
#define UTIL_H
/**
 * Dedicated to general stateless functionality that is useful around the place
 * without having any "architectural" significance.
 */

/**
 * Gives you the lesser of two vales.
 * @param a is one value.
 * @param b is the other value.
 * @return the lesser of the two.
 */
float util_min(float a, float b);

/**
 * Gives you the greater of two values.
 * @param a is one value.
 * @param b is the other.
 * @return the greater of the two.
 */
float util_max(float a, float b);

/**
 * Tells you if a character is whitespace.
 * @param c is the character to test.
 * @return 1 if the character is whitespace and 0 otherwise.
 */
int util_whitespace(char c);

/**
 * Adds two vectors together.
 * @param a is the first vector.
 * @param b is the second vector.
 * @return the result.
 */
struct Vector util_addVector(struct Vector a, struct Vector b);

/**
 * Subtracts one vector from another.
 * @param a is the first vector.
 * @param b is the second vector.
 * @return the result.
 */
struct Vector util_subVector(struct Vector a, struct Vector b);

/**
 * Multiplies two vectors together.
 * @param a is the first vector.
 * @param b is the second vector.
 * @return the result.
 */
struct Vector util_multVector(struct Vector a, struct Vector b);

/**
 * Divides a vector by another.
 * @param a is the first vector.
 * @param b is the second vector.
 * @return the result.
 */
struct Vector util_divVector(struct Vector a, struct Vector b);

#endif
