#include "helpers.hh"
#include <SFML/Graphics.hpp>

void compareVectors(sf::Vector2f a, sf::Vector2f b) {
    INFO("(" << a.x << ", " << a.y << ") == (" << b.x << ", " << b.y << ")?");
    REQUIRE(a.x == Approx(b.x));
    REQUIRE(a.y == Approx(b.y));
}
