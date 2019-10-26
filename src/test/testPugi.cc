#include "test/catch.hh"
#include "test/helpers.hh"
#include "static/xml/pugixml.hpp"

TEST_CASE("image attribute is loaded", "[xml]") {
    char const *file = "<pack image=\"images/sprites.png\" version=\"1.1.1\"><rat name=\"demon-idle\" x=\"0\" y=\"0\" w=\"960\" h=\"144\"/><rat name=\"fire-skull\" x=\"960\" y=\"0\" w=\"768\" h=\"112\"/><rat name=\"nightmare-galloping\" x=\"0\" y=\"144\" w=\"576\" h=\"96\"/><rat name=\"nightmare-idle\" x=\"576\" y=\"144\" w=\"512\" h=\"96\"/><rat name=\"tileset\" x=\"0\" y=\"240\" w=\"512\" h=\"512\"/><rat name=\"fire-skull-no-fire\" x=\"1728\" y=\"0\" w=\"216\" h=\"70\"/><rat name=\"border copy 14\" x=\"1944\" y=\"0\" w=\"48\" h=\"48\"/><rat name=\"border copy 19\" x=\"1992\" y=\"0\" w=\"48\" h=\"48\"/><rat name=\"border copy 24\" x=\"1088\" y=\"144\" w=\"48\" h=\"48\"/><rat name=\"border copy 30\" x=\"1136\" y=\"144\" w=\"48\" h=\"48\"/><rat name=\"buttonPressed copy 64\" x=\"1632\" y=\"144\" w=\"32\" h=\"32\"/><rat name=\"buttonPressed copy 69\" x=\"1664\" y=\"144\" w=\"32\" h=\"32\"/><rat name=\"buttonPressed copy 9\" x=\"1696\" y=\"144\" w=\"32\" h=\"32\"/><rat name=\"buttonPressed\" x=\"1728\" y=\"144\" w=\"32\" h=\"32\"/><rat name=\"bongo copy 2\" x=\"1944\" y=\"48\" w=\"16\" h=\"12\"/><rat name=\"bongo copy 7\" x=\"1960\" y=\"48\" w=\"16\" h=\"12\"/></pack>";
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(file);
    REQUIRE(result);
    pugi::xml_node node = doc.child("pack");
    REQUIRE(node);
    compareStrings(node.attribute("image").value(), "images/sprites.png");
}
