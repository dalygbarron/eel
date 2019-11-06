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

TEST_CASE("trim to buffer", "[utils]") {
    char buffer[50];
    char const *input = "   \n  \nhello you idiots :)\n    ";
    char const *expected = "hello you idiots :)";
    int length = Utils::trimToBuffer(*input, *buffer, 50);
    REQUIRE(length == 19);
    compareStrings(buffer, expected);
}

TEST_CASE("trim to buffer no whitespace", "[utils]") {
    char buffer[50];
    char const *input = "tango is   a cuck";
    char const *expected = "tango is   a cuck";
    int length = Utils::trimToBuffer(*input, *buffer, 50);
    REQUIRE(length == 17);
    compareStrings(buffer, expected);
}

TEST_CASE("trim to buffer not big enough", "[utils]") {
    char buffer[25];
    char const *input = "     123456789012345678901234567890     ";
    char const *expected = "1234567890123456789012345";
    int length = Utils::trimToBuffer(*input, *buffer, 25);
    REQUIRE(length == 25);
    compareStrings(buffer, expected);
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
    int written = Utils::parseBase64String(*input, *output, 5);
    REQUIRE(written == 0);
    REQUIRE(output[0] == 0);
}

TEST_CASE("parse base64 string", "[utils]") {
    char const *input = " VGFuZ28gaXMgYW4gaWRpb3Q=   ";
    unsigned char output[18];
    char const *expected = "Tango is an idiot";
    int written = Utils::parseBase64String(*input, *output, 18);
    REQUIRE(written == 17);
    compareStringToUnsigned(expected, output, written);
}

TEST_CASE("parse base 64 string has whitespace around it", "[utils]") {
    char const *input = "    \nVGFuZ28gaXMgYW4gaWRpb3Q=\n   \n  \n";
    unsigned char output[18];
    char const *expected = "Tango is an idiot";
    int written = Utils::parseBase64String(*input, *output, 18);
    REQUIRE(written == 17);
    compareStringToUnsigned(expected, output, written);
}

TEST_CASE("parse base64 string max length is long", "[utils]") { 
    char const *input = "Y2hhciBjb25zdCAqaW5wdXQgPSAiVkdGdVoyOGdhWFlXZzRnYVdS"
        "cGIzUT0iOw==";
    unsigned char output[200];
    char const *expected = "char const *input = \"VGFuZ28gaXYWg4gaWR"
        "pb3Q=\";";
    int written = Utils::parseBase64String(*input, *output, 200);
    REQUIRE(written == 46);
    compareStringToUnsigned(expected, output, written);
}

TEST_CASE("parse base64 string max length is short", "[utils]") {
    char const *input = "VGFuZ28gaXMgYW4gaWRpb3Q=";
    unsigned char output[6];
    char const *expected = "Tango";
    int written = Utils::parseBase64String(*input, *output, 5);
    REQUIRE(written == 5);
    compareStringToUnsigned(expected, output, written);
}

TEST_CASE("path token", "[utils][path]") {
    char const *test = "~/Documents/github/eel/README.md";
    REQUIRE(Utils::pathToken(test[0]) == 1);
    REQUIRE(Utils::pathToken(test[1]) == 10);
    REQUIRE(Utils::pathToken(test[11]) == 7);
    REQUIRE(Utils::pathToken(test[18]) == 4);
    REQUIRE(Utils::pathToken(test[22]) == 10);
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
