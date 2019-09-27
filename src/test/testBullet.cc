#include "test/catch.hh"
#include "model/Bullet.hh"

TEST_CASE("copy should work", "[bullet]") {
    Bullet a;
    Bullet b;
    b.alive = true;
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

TEST_CASE("copy should fail when copyer is dead", "[bullet]") {
    Bullet a;
    Bullet b;
    a.state.live.radius = 1;
    a.state.live.speed = 2;
    a.state.live.shape = 3;
    b.state.live.radius = 0;
    b.state.live.speed = 0;
    b.state.live.shape = 0;
    b.alive = false;
    b.state.next = &a;
    // Test that an exception is thrown.
    REQUIRE_THROWS(b.copy(&a));
    // test no data changed.
    REQUIRE(b.state.next == &a);
}



TEST_CASE("launch should work", "[bullet][maths]") {

}

TEST_CASE("gravityLaunch should work", "[bullet][maths]") {

}
