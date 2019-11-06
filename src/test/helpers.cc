#include "test/helpers.hh"
#include "catch.hh"
#include <SFML/Graphics.hpp>
#include <string.h>

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

void compareStrings(char const *expected, char const *received) {
    REQUIRE_THAT(received, Catch::Matchers::Equals(expected));
}

void compareStringToUnsigned(
    char const *expected,
    unsigned char const *received,
    int length
) {
    char buffer[length + 1];
    memcpy(buffer, received, length);
    buffer[length] = 0;
    compareStrings(expected, buffer);
}
