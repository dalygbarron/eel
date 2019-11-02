#include "static/Utils.hh"
#include "static/Constant.hh"
#include "static/spdlog/spdlog.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <exception>

float Utils::min(float a, float b) {
    if (a < b) return a;
    else return b;
}

float Utils::max(float a, float b) {
    if (a > b) return a;
    else return b;
}

int Utils::isWhitespace(char c) {
    return (c == ' ' || c == '\n' || c == '\t');
}

int Utils::endOfWord(char const &string) {
    char const *pointer = &string;
    if (!pointer[0]) return 0;
    int i;
    for (i = 1; pointer[i]; i++) {
        if (Utils::isWhitespace(pointer[i])) return i;
    }
    return i;
}

int Utils::startOfNextWord(char const &string) {
    char const *pointer = &string;
    if (!pointer[0]) return 0;
    for (int i = 1; pointer[i]; i++) {
        if (!Utils::isWhitespace(pointer[i] &&
            Utils::isWhitespace(pointer[i - 1]))) {
            return i;
        }
    }
    return 0;
}

int Utils::pathToken(char const &start) {
    char const *pointer = &start;
    int i = 1;
    while (pointer[i] && pointer[i] != '/') i++;
    return i;
}

void Utils::fitText(char const &string, sf::FloatRect bounds, sf::Text &text) {
    char fittedContent[Constant::SMALL_TEXT_BUFFER_SIZE];
    int readHead = 0;
    int writeHead = 0;
    char const *stringPointer = &string;
    while (true) {
        int word = Utils::endOfWord(stringPointer[readHead]);
        if (!word) break;
        if (readHead + word >= Constant::SMALL_TEXT_BUFFER_SIZE) {
            writeHead = Constant::SMALL_TEXT_BUFFER_SIZE - 1;
            spdlog::error(
                "Buffer was too small to fit whole text '{}'",
                stringPointer
            );
            break;
        }
        for (int i = 0; i < word; i++) {
            char c = stringPointer[readHead + i];
            // TODO: format strings and fancy stuff would be cool.
            //       perhaps that would belong in a different function I guess.
            if (c == '\n') fittedContent[writeHead + i] = ' ';
            else if (c == '#') fittedContent[writeHead + i] = '\n';
            else fittedContent[writeHead + i] = stringPointer[readHead + i];
        }
        text.setString(fittedContent);
        sf::FloatRect newBounds = text.getLocalBounds();
        if (newBounds.width > bounds.width) {
            readHead += Utils::startOfNextWord(stringPointer[readHead]);
            fittedContent[writeHead] = '\n';
            writeHead++;
        } else if (newBounds.height > bounds.height) {
            spdlog::warn(
                "Box was too small to fit whole text '{}'",
                stringPointer
            );
            break;
        } else {
            readHead += word;
            writeHead += word;
        }
    }
    fittedContent[writeHead] = 0;
    text.setString(fittedContent);
}

char &Utils::readFile(char const &file) {
    sf::FileInputStream input;
    if (!input.open(&file)) {
        spdlog::error("Can't open file '{}' for reading", &file);
        char *empty = new char[1];
        empty[0] = 0;
        return empty[0];
    }
    int length = input.getSize();
    char *string = new char[length + 1];
    input.read(string, length);
    string[length] = 0;
    return string[0];
}

sf::Vector2f Utils::wrapped(sf::Vector2f pos, sf::FloatRect bounds) {
    while (pos.x < bounds.left) pos.x += bounds.width;
    while (pos.x >= bounds.left + bounds.width) pos.x -= bounds.width;
    while (pos.y < bounds.top) pos.y += bounds.height;
    while (pos.y >= bounds.top + bounds.height) pos.y -= bounds.height;
    return pos;
}

float Utils::random() {
    return (float)rand() / RAND_MAX;
}

sf::View Utils::getLetterboxView(sf::View view, sf::Vector2i dimensions) {
    float windowRatio = dimensions.x / (float)dimensions.y;
    float viewRatio = view.getSize().x / (float)view.getSize().y;
    float sizeX = 1;
    float sizeY = 1;
    float posX = 0;
    float posY = 0;
    int horizontalSpace = true;
    if (windowRatio < viewRatio) horizontalSpace = false;
    if (horizontalSpace) {
        sizeX = viewRatio / windowRatio;
        posX = (1 - sizeX) / 2.f;
    } else {
        sizeY = windowRatio / viewRatio;
        posY = (1 - sizeY) / 2.f;
    }
    view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY));
    return view;
}

int Utils::parseInt(char const &text) {
    return strtol(&text, 0, 0);
}

unsigned int Utils::parseBase64(char c) {
    if (c >= 64 && c < 91) return c - 65;
    else if (c >= 97 && c < 123) return c - 71;
    else if (c >= 48 && c < 58) return c + 4;
    else if (c == '+') return 62;
    else if (c == '/') return 63;
    else if (c == '=') return 0;
    spdlog::error("{} is not a base64 character", (int)c);
    return 0;
}

int Utils::parseBase64String(char const &src, unsigned char &dst, int max) {
    char const *srcPointer = &src;
    unsigned char *dstPointer = &dst;
    int length = strlen(srcPointer);
    if (length % 4 != 0) {
        spdlog::error(
            "Base64 encoded string '{}' should be multiple of 4 in length",
            srcPointer
        );
        return 0;
    }
    int write = 0;
    for (int i = 0; i < length; i += 4) {
        int pads = 0;
        for (int j = i; j < i + 4; j++) {
            if (srcPointer[j] == '=') pads++;
        }
        unsigned int a = Utils::parseBase64(srcPointer[i]);
        unsigned int b = Utils::parseBase64(srcPointer[i + 1]);
        unsigned int c = Utils::parseBase64(srcPointer[i + 2]);
        unsigned int d = Utils::parseBase64(srcPointer[i + 3]);
        unsigned int value = a << 18 | b << 12 | c << 6 | d;
        int stop = write + 3 - pads;
        while (write < stop && write < max) {
            dstPointer[write] = (value & 0xff0000) >> 16;
            value <<= 8;
            write++;
        }
    }
    dstPointer[write] = 0;
    return write;
}

pugi::xml_node Utils::openXml(
    pugi::xml_document &doc,
    char const &tag,
    char const &string
) {
    pugi::xml_parse_result result = doc.load_string(&string);
    if (!result) {
        spdlog::error("xml is not valid: {}", result.description());
        throw std::invalid_argument("invalid xml");
    }
    pugi::xml_node node = doc.child(&tag);
    if (!node) {
        spdlog::error("xml lacks top level node '{}'", &tag);
        throw std::invalid_argument("xml lacks required tag");
    }
    return node;
}

std::size_t Utils::VectHash::operator()(sf::Vector2i const &v) const noexcept {
    return v.x ^ v.y;
}
