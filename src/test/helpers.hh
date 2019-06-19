#ifndef HELPERS_HH
#define HELPERS_HH

#include "catch.hh"
#include <SFML/Graphics.hpp>

/**
 * Asserts that two vectors are the same in such a way that you can see their details if it fails which is nice.
 * @param a is the first vector.
 * @param b is the second vector.
 */
void compareVectors(sf::Vector2f a, sf::Vector2f b);

#endif
