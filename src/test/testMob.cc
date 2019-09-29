#include "test/catch.hh"
#include "model/Placement.hh"
#include "static/spdlog/spdlog.h"

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
    Mob const *test[] = {&a, &b, &c, &d, &e, &f, &g};
    sf::Vector2u dirty = Mob::sort(test, 7);
    REQUIRE(dirty.x == -1);
    REQUIRE(dirty.y == -1);
    for (int i = 0; i < 7; i++) REQUIRE(correct[i] == test[i]);
    // test that in the worst case everything is dirty and also it works.
    test[0] = &g;
    test[1] = &f;
    test[2] = &e;
    test[3] = &d;
    test[4] = &c;
    test[5] = &b;
    test[6] = &a;
    dirty = Mob::sort(test, 7);
    REQUIRE(dirty.x == 0);
    REQUIRE(dirty.y == 6);
    for (int i = 0; i < 7; i++) REQUIRE(correct[i] == test[i]);
    // test some kinda arbitrary bit to see how the dirty thing goes.
    test[0] = &a;
    test[1] = &b;
    test[2] = &e;
    test[3] = &d;
    test[4] = &c;
    test[5] = &f;
    test[6] = &g;
    dirty = Mob::sort(test, 7);
    REQUIRE(dirty.x == 2);
    REQUIRE(dirty.y == 4);
    for (int i = 0; i < 7; i++) REQUIRE(correct[i] == test[i]);
    // test that if you put a single bad thing in the start it all gets dirty.
    test[0] = &e;
    test[1] = &a;
    test[2] = &b;
    test[3] = &c;
    test[4] = &d;
    test[5] = &f;
    test[6] = &g;
    dirty = Mob::sort(test, 7);
    REQUIRE(dirty.x == 0);
    REQUIRE(dirty.y == 4);
    for (int i = 0; i < 7; i++) REQUIRE(correct[i] == test[i]);
}

TEST_CASE("sorting mobs speed", "[mob][maths][speed]") {
    Mob *mobs = new Mob[40000];
    Mob const *constMobs[40000];
    for (int i = 0; i < 40000; i++) mobs[i].position.y = rand() % 40000;
    for (int i = 0; i < 40000; i++) constMobs[i] = mobs + i;
    // Sorting from random case.
    sf::Clock clock;
    Mob::sort(constMobs, 40000);
    float badTime = clock.getElapsedTime().asSeconds();
    spdlog::info("{}", clock.getElapsedTime().asSeconds());
    for (int i = 1; i < 40000; i++) {
        REQUIRE(!constMobs[i]->behind(constMobs[i - 1]));
    }
    // Sorting from a case with few errors.
    for (int i = 0; i < 10; i++) {
        mobs[rand() % 40000].position.y = rand() % 40000;
    }
    clock.restart();
    Mob::sort(constMobs, 40000);
    float goodTime = clock.getElapsedTime().asSeconds();
    REQUIRE(goodTime < badTime);
    spdlog::info("{}", clock.getElapsedTime().asSeconds());
    for (int i = 1; i < 40000; i++) {
        REQUIRE(!constMobs[i]->behind(constMobs[i - 1]));
    }
    // sorting from perfect case
    clock.restart();
    Mob::sort(constMobs, 40000);
    float bestTime = clock.getElapsedTime().asSeconds();
    REQUIRE(bestTime < goodTime);
    spdlog::info("{}", clock.getElapsedTime().asSeconds());
    for (int i = 1; i < 40000; i++) {
        REQUIRE(!constMobs[i]->behind(constMobs[i - 1]));
    }
    // Sorting two sub lists.
    for (int i = 0; i < 40000; i++) {
        mobs[i].position.y = i % 30000;
        constMobs[i] = mobs + i;
    }
    clock.restart();
    Mob::sort(constMobs, 40000);
    spdlog::info("{}", clock.getElapsedTime().asSeconds());
    for (int i = 1; i < 40000; i++) {
        REQUIRE(!constMobs[i]->behind(constMobs[i - 1]));
    }
}
