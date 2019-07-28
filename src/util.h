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

/**
 * Hashes a string into a number.
 * @param string is the string to hash.
 * @return a numerical hash of that string which is unbounded except by some
 *         arbitrary technical value which doesn't matter.
 */
int util_hashString(char const *string);

/**
 * Creates a dictionary. Basically just an array of linked lists that have
 * a specific size.
 */
struct Bucket *util_createDictionary();

/**
 * Adds an item into a dictionary with the given key.
 * @param bucket is a pointer to the dictionary start.
 * @param key    is the key by which to store it in the dictionary.
 * @param value  is the value to store in the dictionary.
 */
void util_addToDictionary(struct Bucket *bucket, char const *key, void *value);

/**
 * Finds a value in a dictionary stored by a given key.
 * @param bucket is the dictionary to look in.
 * @parma key    is the key to find.
 * @return the item if found or null if nothing found.
 */
void *util_findInDictionary(struct Bucket *bucket, char const *key);

/**
 * Destroys a dictionary and it's contents.
 * @param bucket is a pointer to the dictionary.
 */
void util_destroyDictionary(struct Bucket *bucket);

/**
 * Takes a bucket and recursively destroys all contents.
 * @param bucket is the bucket to destroy.
 */
void util_destroyBucket(struct Bucket *bucket);

#endif
