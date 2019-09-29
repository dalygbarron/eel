#include "test/catch.hh"
#include "model/Placement.hh"

TEST_CASE("comparing mobs", "[mob][maths]") {
    Placement a;
    Placement b;
    a.position.x = 5;
    b.position.x = 6;
    a.position.y = 0;
    b.position.y = 0;
    a.position.z = 0;
    b.position.z = 0;
    // x position should be irrelevant and should not be behind themselves.
    REQUIRE(!a.behind(&b));
    REQUIRE(!a.behind(&a));
    REQUIRE(!b.behind(&a));
    // other positions are releavant.
    a.position.y = 1;
    REQUIRE(b.behind(&a));
    REQUIRE(!a.behind(&b));
    // TODO: I don't think I have the logic of this function fully fleshed out.
}

TEST_CASE("sorting mobs", "[mob][maths]") {
    Placement a;
    Placement b;
    Placement c;
    Placement d;
    Placement e;
    Placement f;
    Placement g;
    a.position.y = 1;
    b.position.y = 2;
    c.position.y = 3;
    d.position.y = 4;
    e.position.y = 5;
    f.position.y = 6;
    g.position.y = 7;
    Mob *correct[] = {&a, &b, &c, &d, &e, &f, &g};
    // test that when it's already right it does nothing.
    Mob *test[] = {&a, &b, &c, &d, &e, &f, &g};
    sf::Vector2u dirty = Mob::sort(test, 7);
    REQUIRE(dirty.x == -1);
    REQUIRE(dirty.y == -1);
    for (int i = 0; i < 7; i++) REQUIRE(correct[i] == test[i]);
    // test that in the worst case everything is dirty and also it works.
    test = {&g, &f, &e, &d, &c, &b, &a};
    dirty = Mob::sort(test, 7);
    REQUIRE(dirty.x == 0);
    REQUIRE(dirty.y == 6);
    for (int i = 0; i < 7; i++) REQUIRE(correct[i] == test[i]);
    // test some kinda arbitrary bit to see how the dirty thing goes.
    test = {&a, &b, &e, &d, &c, &f, &g};
    dirty = Mob::sort(test, 7);
    REQUIRE(dirty.x == 2);
    REQUIRE(dirty.y == 4);
    for (int i = 0; i < 7; i++) REQUIRE(correct[i] == test[i]);
}
