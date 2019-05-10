#include <iostream>
#include <SFML/Graphics.hpp>


/**
 * Start of the program.
 * @param argc is the number of commandline arguments given.
 * @param argv is an array of commandline arguments as pointers to strings.
 * @return 0 when program exits expectedly, and otherwise returns something else probably meaningless.
 */
int main(int argc, char **argv) {
    sf::Font font;
    sf::Texture texture;
    if (!font.loadFromFile("test/font/bocklin.ttf") || !texture.loadFromFile("test/image/bg.png")) {
        return -1;
    }
    texture.setRepeated(true);
    texture.setSmooth(true);

    sf::RenderWindow window(sf::VideoMode(1920, 1440), "World of Piss");
    window.setFramerateLimit(60);
    sf::RectangleShape shape(sf::Vector2f(640, 480));
    //shape.setOutlineThickness(5);
    //shape.setOutlineColor(sf::Color::White);
    shape.setTexture(&texture);
    shape.setPosition(500, 500);
    sf::Text text;
    text.setFont(font);
    text.setString("League of Piss");
    text.setCharacterSize(40);
    text.setFillColor(sf::Color::White);
    text.setPosition(640, 490);
    sf::RectangleShape background(sf::Vector2f(960, 1440));
    background.setPosition(480, 0);
    background.setTextureRect(sf::IntRect(0, 0, 1, 1));
    sf::Shader shader;
    if (!shader.loadFromFile("test/shader/plain.vert", "test/shader/plain.frag")) {
        return -1;
    }
    shader.setUniform("resolution", sf::Vector2f(1920, 1440));


    int i = 0;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        shader.setUniform("time", i / 60.f);
        shape.setTextureRect(sf::IntRect(i, i / -2, 200, 200));
        window.clear();
        window.draw(background, &shader);
        window.draw(shape);
        window.draw(text);
        window.display();
        i++;
    }

    return 0;
}
