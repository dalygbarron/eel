#include "test/catch.hh"
#include "test/helpers.hh"
#include "static/Utils.hh"
#include "static/spdlog/spdlog.h"
#include <SFML/Graphics.hpp>

TEST_CASE("min", "[utils][maths]") {
    using namespace Catch::literals;
    REQUIRE(Utils::min(1, 2) == 1);
    REQUIRE(Utils::min(69.91, 5.3) == 5.3_a);
}

TEST_CASE("max", "[utils][maths]") {
    using namespace Catch::literals;
    REQUIRE(Utils::max(1, 2) == 2);
    REQUIRE(Utils::max(69.91, 5.3) == 69.91_a);
}

TEST_CASE("wrapped works", "[utils][maths]") {
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
    compareVectors(
        Utils::wrapped(sf::Vector2f(5, 5), sf::FloatRect(5, 5, 2, 2)),
        sf::Vector2f(5, 5)
    );
    compareVectors(
        Utils::wrapped(sf::Vector2f(4.9, 4), sf::FloatRect(5, 5, 2, 2)),
        sf::Vector2f(6.9, 6)
    );
    compareVectors(
        Utils::wrapped(sf::Vector2f(7, 9), sf::FloatRect(5, 4, 2, 2)),
        sf::Vector2f(5, 5)
    );
    compareVectors(
        Utils::wrapped(sf::Vector2f(0, 0), sf::FloatRect(2.1, 1.2, 5.8, 0.2)),
        sf::Vector2f(5.8, 1.2)
    );
}

TEST_CASE("random", "[utils][maths]") {
    for (int i = 0; i < 10; i++) {
        float value = Utils::random();
        REQUIRE(value >= 0);
        REQUIRE(value <= 1);
    }
}

TEST_CASE("parseInt", "[utils]") {
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

TEST_CASE("parse base 64", "[utils]") {
    REQUIRE(Utils::parseBase64('A') == 0);
    REQUIRE(Utils::parseBase64('E') == 4);
    REQUIRE(Utils::parseBase64('Z') == 25);
    REQUIRE(Utils::parseBase64('a') == 26);
    REQUIRE(Utils::parseBase64('j') == 35);
    REQUIRE(Utils::parseBase64('z') == 51);
    REQUIRE(Utils::parseBase64('0') == 52);
    REQUIRE(Utils::parseBase64('9') == 61);
    REQUIRE(Utils::parseBase64('+') == 62);
    REQUIRE(Utils::parseBase64('/') == 63);
}

TEST_CASE("parse base64 empty string", "[utils]") {
    char const *input = "";
    unsigned char output[5];
    int written = Utils::parseBase64String(input, output, 5);
    REQUIRE(written == 0);
    REQUIRE(output[0] == 0);
}

TEST_CASE("parse base64 string", "[utils]") {
    char const *input = "VGFuZ28gaXMgYW4gaWRpb3Q=";
    unsigned char output[18];
    char const *expected = "Tango is an idiot";
    int written = Utils::parseBase64String(input, output, 18);
    REQUIRE(written == 17);
    for (int i = 0; i < 18; i++) REQUIRE(output[i] == expected[i]);
}

TEST_CASE("parse base64 string max length is long", "[utils]") { 
    char const *input = "Y2hhciBjb25zdCAqaW5wdXQgPSAiVkdGdVoyOGdhWFlXZzRnYVdS"
        "cGIzUT0iOw==";
    unsigned char output[200];
    char const *expected = "char const *input = \"VGFuZ28gaXYWg4gaWRpb3Q=\";";
    int written = Utils::parseBase64String(input, output, 200);
    REQUIRE(written == 46);
    for (int i = 0; i < 47; i++) REQUIRE(output[i] == expected[i]);
}

TEST_CASE("parse base64 string max length is short", "[utils]") {
    char const *input = "VGFuZ28gaXMgYW4gaWRpb3Q=";
    unsigned char output[6];
    char const *expected = "Tango";
    int written = Utils::parseBase64String(input, output, 5);
    REQUIRE(written == 5);
    for (int i = 0; i < 6; i++) REQUIRE(output[i] == expected[i]);
}

TEST_CASE("path token", "[utils][path]") {
    char const *test = "~/Documents/github/eel/README.md";
    REQUIRE(Utils::pathToken(test) == 1);
    REQUIRE(Utils::pathToken(test + 1) == 10);
    REQUIRE(Utils::pathToken(test + 11) == 7);
    REQUIRE(Utils::pathToken(test + 18) == 4);
    REQUIRE(Utils::pathToken(test + 22) == 10);
}

TEST_CASE("getLetterboxView", "[utils][graphics][maths]") {
    sf::View view;
    // on a small unit square.
    view.setViewport(sf::FloatRect(0, 0, 1, 1));
    compareRects(
        Utils::getLetterboxView(view, sf::Vector2i(1, 1)).getViewport(),
        sf::FloatRect(0, 0, 1, 1)
    );
    compareRects(
        Utils::getLetterboxView(view, sf::Vector2i(2, 1)).getViewport(),
        sf::FloatRect(0.25, 0, 0.5, 1)
    );
    compareRects(
        Utils::getLetterboxView(view, sf::Vector2i(1, 2)).getViewport(),
        sf::FloatRect(0, 0.25, 1, 0.5)
    );
    compareRects(
        Utils::getLetterboxView(view, sf::Vector2i(2, 2)).getViewport(),
        sf::FloatRect(0, 0, 1, 1)
    );
    // on a wacky shape.
    view.setViewport(sf::FloatRect(0, 0, 324, 543));
    compareRects(
        Utils::getLetterboxView(view, sf::Vector2i(333, 111)).getViewport(),
        sf::FloatRect(0.33333, 0, 0.33333, 1)
    );

}

TEST_CASE("fitQuad", "[utils][graphics]") {
    sf::VertexArray vertices(sf::Quads, 10);
    Utils::fitQuad(&vertices[0], sf::FloatRect());
    // make sure the vertices are in the right places.
    // TODO: this.
    REQUIRE(false);
}

TEST_CASE("colourQuad", "[utils][graphics]") {
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

TEST_CASE("makeBox") {
    // TODO: this.
    REQUIRE(false);
}
