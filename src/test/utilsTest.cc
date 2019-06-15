#include "tests.hh"
#include "../Utils.hh"

TEST_CASE("test wrapped works", "[utils]") {
    // TODO: this.
}

TEST_CASE("test random works", "[utils]") {
    for (int i = 0; i < 10; i++) {
        float value = Utils::random();
        REQUIRE(value >= 0);
        REQUIRE(value <= 1);
    }
}

TEST_CASE("per pixel works", "[utils]") {
    REQUIRE(Utils::perSecond(90) == 1.5);
    REQUIRE(Utils::perSecond(60) == 1);
    REQUIRE(Utils::perSecond(30) == 0.5);
    REQUIRE(Utils::perSecond(15) == 0.25);
    REQUIRE(Utils::perSecond(6) == 0.1);
}

TEST_CASE("per pixel per pixel works", "[utils]") {
    REQUIRE(Utils::perSecond(3600) == 1);
    REQUIRE(Utils::perSecond(60) == 0.01777);
    REQUIRE(Utils::perSecond(45) == 0.0125);
}
