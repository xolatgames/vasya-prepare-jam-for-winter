#include "../include/background.hpp"

Background::Background()
{
    backgroundImage.loadFromFile("png/background.png");
    backgroundTexture.loadFromImage(backgroundImage);
    backgroundSprite.setTexture(backgroundTexture);
    backgroundSprite.setTextureRect(sf::IntRect(0, 0, 1280, 800));

    sunImage.loadFromFile("png/back/sun.png");
    sunTexture.loadFromImage(sunImage);
    sunSprite.setTexture(sunTexture);
    sunSprite.setOrigin(sf::Vector2f(128, 128));
    sunSprite.setTextureRect(sf::IntRect(0, 0, 256, 256));
    sunSprite.setPosition(sf::Vector2f(1024, 256));

    for ( int i=0; i < 10; i++ )
    {
        clouds.push_back(new Cloud(i));
    }
}

void Background::Draw(sf::RenderWindow &window, float cameraX)
{
    window.draw(backgroundSprite);
    window.draw(sunSprite);

    for ( unsigned int i=0; i < clouds.size(); i++ )
    {
        clouds.at(i)->Draw(window, cameraX);
    }
}
