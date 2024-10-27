#include <SFML/Graphics.hpp>
#include "../include/jam.hpp"

Jam::Jam(float jamX, float jamY)
{

    jamImage.loadFromFile("png/jam.png");
    jamTexture.loadFromImage(jamImage);
    jamSprite.setTexture(jamTexture);
    jamSprite.setOrigin(sf::Vector2f(128, 128));
    jamSprite.setTextureRect(sf::IntRect(0, 0, 256, 256));
    jamSprite.setPosition(sf::Vector2f(jamX, jamY));
    jamSprite.setScale(sf::Vector2f(0.25, 0.25));
}

void Jam::Draw(sf::RenderWindow &window, float cameraX)
{
    jamSprite.setPosition( jamSprite.getPosition() - sf::Vector2f(cameraX, 0) );
    window.draw(jamSprite);
}
