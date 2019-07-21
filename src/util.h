#ifndef UTIL_H
#define UTIL_H

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

#endif
