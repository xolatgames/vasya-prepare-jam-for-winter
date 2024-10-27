#include <SFML/Graphics.hpp>
#include "../include/ground.hpp"

Ground::Ground(int image, float groundX, float groundY)
{
    switch (image)
    {
        case Image::Top:
        {
            groundImage.loadFromFile("png/ground_top.png");
        }
        break;

        case Image::Center:
        {
            groundImage.loadFromFile("png/ground.png");
        }
        break;
    }

    groundTexture.loadFromImage(groundImage);

    groundSprite.setTexture(groundTexture);
    groundSprite.setOrigin(sf::Vector2f(32, 32));
    groundSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    groundSprite.setPosition(sf::Vector2f(groundX, groundY));
}

void Ground::Draw(sf::RenderWindow &window, float cameraX)
{
    groundSprite.setPosition( groundSprite.getPosition() - sf::Vector2f(cameraX, 0) );
    window.draw(groundSprite);
}
