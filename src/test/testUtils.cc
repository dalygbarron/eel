#include "catch.hh"
#include "../Utils.hh"

TEST_CASE("test wrapped works", "[utils]") {
    // TODO: this.
    REQUIRE(false);
}

TEST_CASE("test random works", "[utils]") {
    for (int i = 0; i < 10; i++) {
        float value = Utils::random();
        REQUIRE(value >= 0);
        REQUIRE(value <= 1);
    }
}

TEST_CASE("per pixel works", "[utils]") {
    using namespace Catch::literals;
    REQUIRE(Utils::perSecond(90) == 1.5_a);
    REQUIRE(Utils::perSecond(60) == 1_a);
    REQUIRE(Utils::perSecond(30) == 0.5_a);
    REQUIRE(Utils::perSecond(15) == 0.25_a);
    REQUIRE(Utils::perSecond(6) == 0.1_a);
}

TEST_CASE("per pixel per pixel works", "[utils]") {
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

TEST_CASE("Get letterbox view works", "[utils][graphics]") {
    // TODO: this.
    REQUIRE(false);
}

TEST_CASE("Rect Quad builder works", "[utils][graphics]") {
    // TODO: this.
    REQUIRE(false);
}
