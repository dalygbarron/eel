#include "test/catch.hh"
#include "model/Path.hh"

TEST_CASE("path token", "[path]") {
    char const *test = "~/Documents/github/eel/README.md";
    REQUIRE(Path::token(test) == 1);
    REQUIRE(Path::token(test + 1) == 10);
    REQUIRE(Path::token(test + 11) == 7);
    REQUIRE(Path::token(test + 18) == 4);
    REQUIRE(Path::token(test + 22) == 10);
}

TEST_CASE("making nice paths", "[path]") {
    Path path;
    path.apply("camel/pictures");
    path.apply("../sounds/gravel.mp3");
    char const *expected = "camel/sounds/gravel.mp3";
    char const *result = path.render();
    for (int i = 0; expected[i]; i++) REQUIRE(expected[i] == result[i]);
    // also test copy constructor.
    Path babby(&path);
    result = babby.render();
    for (int i = 0; expected[i]; i++) REQUIRE(expected[i] == result[i]);
}

TEST_CASE("make path that is too big", "[path]") {
    // TODO: this.
    REQUIRE(false);
}
