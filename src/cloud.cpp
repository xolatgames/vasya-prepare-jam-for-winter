#include <SFML/Graphics.hpp>
#include <random>
#include <ctime>
#include "../include/cloud.hpp"

Cloud::Cloud(int rand_seed)
{
    image.loadFromFile("png/back/cloud.png");
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(128, 64));
    sprite.setTextureRect(sf::IntRect(0, 0, 256, 128));

    time_t t;

    srand(time(&t) + rand_seed);
    x = (float)rand() / RAND_MAX * 1280;
    y = (float)rand() / RAND_MAX * 400 + 64;
    speed = (float)rand() / RAND_MAX + 1;

    sprite.setScale(sf::Vector2f(speed / 2, speed / 2));
    sprite.setPosition(sf::Vector2f(x, y));
}

void Cloud::Update()
{
    sprite.move(sf::Vector2f(-speed / 5, 0));

    if ( sprite.getPosition().x < -128 )
    {
        sprite.setPosition(sf::Vector2f(1408, y));
    }
    else if ( sprite.getPosition().x > 1408 )
    {
        sprite.setPosition(sf::Vector2f(-128, y));
    }
}

void Cloud::Draw(sf::RenderWindow &window, float cameraX)
{
    sprite.setPosition( sprite.getPosition() - sf::Vector2f(cameraX / 2, 0) );
    window.draw(sprite);
}
