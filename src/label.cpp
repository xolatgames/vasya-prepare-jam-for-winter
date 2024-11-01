#include <SFML/Graphics.hpp>
#include "../include/label.hpp"

Label::Label(string text, float x, float y)
{
    font.loadFromFile("DejaVuSans.ttf");

    label.setFont(font);
    label.setCharacterSize(20);
    label.setFillColor(sf::Color::White);
    label.setOutlineColor(sf::Color::Black);
    label.setOutlineThickness(1);
    label.setPosition(x, y);
    label.setString(text);
}

void Label::Draw(sf::RenderWindow &window, float cameraX)
{
    label.setPosition( label.getPosition() - sf::Vector2f(cameraX, 0) );
    window.draw(label);
}
