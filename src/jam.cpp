#include <SFML/Graphics.hpp>
#include "../include/jam.hpp"

Jam::Jam(float x, float y)
{

    image.loadFromFile("png/jam.png");
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(128, 128));
    sprite.setTextureRect(sf::IntRect(0, 0, 256, 256));
    sprite.setPosition(sf::Vector2f(x, y));
    sprite.setScale(sf::Vector2f(0.25, 0.25));
}

void Jam::Update()
{
    mask = sprite.getGlobalBounds();
    mask.left += 24;
    mask.width -= 40;
    mask.top += 24;
    mask.height -= 40;
}

void Jam::Draw(sf::RenderWindow &window, float cameraX)
{
    sprite.setPosition( sprite.getPosition() - sf::Vector2f(cameraX, 0) );
    window.draw(sprite);
}
