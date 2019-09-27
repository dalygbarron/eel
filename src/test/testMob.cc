#include "test/tests.hh"
#include "test/catch.hh"
#include "model/Placement.hh"

TEST_CASE("comparing mobs", "[maths]") {
    Placement a;
    Placement b;
    a.position.x = 5;
    b.position.x = 6;
    a.position.y = 0;
    b.position.y = 0;
    a.position.z = 0;
    b.position.z = 0;
    // x position should be irrelevant
    REQUIRE(!a.behind(&b));
    REQUIRE(!b.behind(&a));
    // other positions are releavant.
    a.position.y = 1;
    REQUIRE(b.behind(&a));
    // TODO: I don't think I have the logic of this function fully fleshed out.
}

TEST_CASE("sorting mobs", "[maths][efficiency]") {
    Placement a;
    Placement b;
    Placement c;
    Placement d;
    Placement e;
    Placement f;
    Placement g;

}
