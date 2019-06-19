#include "catch.hh"
#include "../Utils.hh"
#include "helpers.hh"
#include <SFML/Graphics.hpp>

TEST_CASE("test wrapped works", "[utils][maths]") {
    // test it with rectangles with top left corner at origin.
    compareVectors(
        Utils::wrapped(sf::Vector2f(1, 1), sf::FloatRect(0, 0, 1, 1)),
        sf::Vector2f(0, 0)
    );
    compareVectors(
        Utils::wrapped(sf::Vector2f(2, 3), sf::FloatRect(0, 0, 1, 1)),
        sf::Vector2f(0, 0)
    );
    compareVectors(
        Utils::wrapped(sf::Vector2f(2.5, 3.7), sf::FloatRect(0, 0, 2, 1.5)),
        sf::Vector2f(0.5, 0.7)
    );
    compareVectors(
        Utils::wrapped(sf::Vector2f(2.5, 3.7), sf::FloatRect(0, 0, 2, 2)),
        sf::Vector2f(0.5, 1.7)
    );
    compareVectors(
        Utils::wrapped(sf::Vector2f(-0.5, -3.7), sf::FloatRect(0, 0, 9, 2)),
        sf::Vector2f(8.5, 0.3)
    );
    // test it works with arbitrary rectangles
    // TODO: this.
    REQUIRE(false);
}

TEST_CASE("test random works", "[utils][maths]") {
    for (int i = 0; i < 10; i++) {
        float value = Utils::random();
        REQUIRE(value >= 0);
        REQUIRE(value <= 1);
    }
}

TEST_CASE("per pixel works", "[utils][maths]") {
    using namespace Catch::literals;
    REQUIRE(Utils::perSecond(90) == 1.5_a);
    REQUIRE(Utils::perSecond(60) == 1_a);
    REQUIRE(Utils::perSecond(30) == 0.5_a);
    REQUIRE(Utils::perSecond(15) == 0.25_a);
    REQUIRE(Utils::perSecond(6) == 0.1_a);
}

TEST_CASE("per pixel per pixel works", "[utils][maths]") {
    using namespace Catch::literals;
    REQUIRE(Utils::perSecondPerSecond(3600) == 1_a);
    REQUIRE(Utils::perSecondPerSecond(60) == 0.016666666_a);
    REQUIRE(Utils::perSecondPerSecond(45) == 0.0125_a);
}

TEST_CASE("parsing ints works", "[utils]") {
    // Test normal numbers.
    REQUIRE(Utils::parseInt("12") == 12);
    REQUIRE(Utils::parseInt("1") == 1);
    REQUIRE(Utils::parseInt("-123") == -123);
    REQUIRE(Utils::parseInt("100!!!!! hell yeah!") == 100);
    // Test hexadecimal and octal forms.
    REQUIRE(Utils::parseInt("0x14") == 20);
    REQUIRE(Utils::parseInt("0xBEEF") == 48879);
    REQUIRE(Utils::parseInt("-0xBEEF") == -48879);
    REQUIRE(Utils::parseInt("012") == 10);
    REQUIRE(Utils::parseInt("-0101") == -65);
    // Test invalids.
    REQUIRE(Utils::parseInt("09") == 0);
    REQUIRE(Utils::parseInt("Bongo") == 0);
    REQUIRE(Utils::parseInt("") == 0);
}

TEST_CASE("Get letterbox view works", "[utils][graphics][maths]") {
    // TODO: this.
    REQUIRE(false);
}

TEST_CASE("fit quad works", "[utils][graphics]") {
    sf::VertexArray vertices(sf::Quads, 10);
    Utils::fitQuad(&vertices[0], sf::FloatRect());
    // make sure the vertices are in the right places.
}

TEST_CASE("colour quad works", "[utils][graphics]") {
    sf::VertexArray vertices(sf::Quads, 6);
    Utils::colourQuad(&vertices[0], sf::Color::Red);
    Utils::colourQuad(&vertices[2], sf::Color::Green);
    // make sure the vertices have the right colours
    REQUIRE(vertices[0].color == sf::Color::Red);
    REQUIRE(vertices[1].color == sf::Color::Red);
    REQUIRE(vertices[2].color == sf::Color::Green);
    REQUIRE(vertices[3].color == sf::Color::Green);
    REQUIRE(vertices[4].color == sf::Color::Green);
    REQUIRE(vertices[5].color == sf::Color::Green);
}
