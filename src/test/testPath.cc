#include "test/catch.hh"
#include "test/helpers.hh"
#include "model/Path.hh"

TEST_CASE("path is created", "[path]") {
    char const *root = "example/game.xml";
    char const *base = "maps/big.tmx";
    char const *extra = "../tilesets/outside.tsx";
    char const *firstExpected = "example/maps/big.tmx";
    char const *secondExpected = "example/tilesets/outside.tsx";
    Path basePath(root, base);
    Path tilesetPath(base, extra);
    Path tilesetPathRooted(root, tilesetPath.get());
    compareStrings(firstExpected, basePath.get());
    compareStrings(secondExpected, tilesetPathRooted.get());
}

TEST_CASE("path ignores slashes at start of file path", "[path]") {
    char const *root = "/var/opt/idiot.txt";
    char const *file = "//////..///////bin/////camera.php";
    char const *expected = "/var/bin/camera.php";
    Path path(root, file);
    compareStrings(expected, path.get());
}

TEST_CASE("real life bug", "[path]") {
    char const *root = "sprites.xml";
    char const *file = "images/sprites.png";
    char const *expected = "images/sprites.png";
    Path path(root, file);
    compareStrings(expected, path.get());
}

TEST_CASE("path cannot overrun it's buffer", "[path]") {
    // TODO: this.
    REQUIRE(false);
}
