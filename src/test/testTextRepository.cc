#include "test/catch.hh"
#include "test/helpers.hh"
#include "service/repository/TextRepository.hh"

TEST_CASE(
    "Text if node returned from xml thing is dead",
    "[text][repository][xml]"
) {
    // Requires you to run it where these files are found so it's a functional
    // test I guess. Also it sucks and is brittle as hell but whatever.
    TextRepository textRepo("example");
    pugi::xml_node node = textRepo.getXml("example/sprites.xml", "pack");
    REQUIRE(node);
    compareStrings(node.attribute("image").value(), "images/sprites.png");
}
