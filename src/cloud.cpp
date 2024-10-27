#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>
#include "../include/cloud.hpp"

Cloud::Cloud(int rand_seed)
{
    cloudImage.loadFromFile("png/back/cloud.png");
    cloudTexture.loadFromImage(cloudImage);
    cloudSprite.setTexture(cloudTexture);
    cloudSprite.setOrigin(sf::Vector2f(128, 64));
    cloudSprite.setTextureRect(sf::IntRect(0, 0, 256, 128));

    time_t t;

    srand(time(&t) + rand_seed);
    cloudX = (float)rand() / RAND_MAX * 1280;
    cloudY = (float)rand() / RAND_MAX * 400 + 64;
    cloudSpeed = (float)rand() / RAND_MAX + 1;

    cloudSprite.setScale(sf::Vector2f(cloudSpeed / 2, cloudSpeed / 2));
    cloudSprite.setPosition(sf::Vector2f(cloudX, cloudY));
}

void Cloud::Update()
{
    cloudSprite.move(sf::Vector2f(-cloudSpeed / 5, 0));

    if ( cloudSprite.getPosition().x < -128 )
    {
        cloudSprite.setPosition(sf::Vector2f(1408, cloudY));
    }
    else if ( cloudSprite.getPosition().x > 1408 )
    {
        cloudSprite.setPosition(sf::Vector2f(-128, cloudY));
    }
}

void Cloud::Draw(sf::RenderWindow &window, float cameraX)
{
    cloudSprite.setPosition( cloudSprite.getPosition() - sf::Vector2f(cameraX / 2, 0) );
    window.draw(cloudSprite);
}
