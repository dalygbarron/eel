#include "catch.hh"
#include <SFML/Graphics.hpp>

void compareVectors(sf::Vector2f a, sf::Vector2f b) {
    INFO("(" << a.x << ", " << a.y << ") == (" << b.x << ", " << b.y << ")?");
    REQUIRE(a.x == Approx(b.x));
    REQUIRE(a.y == Approx(b.y));
}

void compareRects(sf::FloatRect a, sf::FloatRect b) {
    INFO(
        "(" << a.left << ", " << a.top << ", " << a.width << ", " << a.height << ") == (" << b.left << ", " << b.top <<
        ", " << b.width << ", " << b.height << ")?"
    );
    REQUIRE(a.left == Approx(b.left));
    REQUIRE(a.top == Approx(b.top));
    REQUIRE(a.width == Approx(b.width));
    REQUIRE(a.height == Approx(b.height));
}
