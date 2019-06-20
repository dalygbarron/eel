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

/**
 * Asserts that two rectangles are the same in such a way that you can see their details if it fails.
 * @param a is the first rectangle.
 * @param b is the second rectangle.
 */
void compareRects(sf::FloatRect a, sf::FloatRect b);

/**
 * Compares a viewport to a rectangle.
 * @param view is the viewport to compare.
 * @param shape is the rectangle. Technically the viewport just returns us a rectangle but it's easier to pass it in.
 */
void compareViewport(sf::View view, sf::FloatRect shape);

#endif
