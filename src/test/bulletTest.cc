#include "tests.hh"
#include "../Bullet.hh"

TEST_CASE("Copy constructor works", "[bullet]") {
    Bullet a;
    Bullet b;
    a.state.live.radius = 1;
    a.state.live.speed = 2;
    a.state.live.shape = 3;
    b.state.live.radius = 0;
    b.state.live.speed = 0;
    b.state.live.shape = 0;
    b.copy(&a);
    // Test that the copy got all relevant properties.
    REQUIRE(b.state.live.radius == 1);
    REQUIRE(b.state.live.speed == 2);
    REQUIRE(b.state.live.shape == 3);
    // Test that copy left the rest alone.
}

TEST_CASE("launch works", "[bullet]") {

}

TEST_CASE("gravity launch works", "[bullet]") {

}
