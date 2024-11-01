#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "../../include/enemy/turtle.hpp"
#include "../../include/ground.hpp"

using namespace std;

Turtle::Turtle(float x, float y)
{
    image1.loadFromFile("png/enemy/turtle1.png");
    image2.loadFromFile("png/enemy/turtle2.png");
    texture1.loadFromImage(image1);
    texture2.loadFromImage(image2);
    sprite.setTexture(texture1);
    sprite.setOrigin(sf::Vector2f(32, 32));
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(sf::Vector2f(x, y));

    walkBuffer.loadFromFile("sound/walk.wav");
    walkSound.setBuffer(walkBuffer);

    spriteFrame = 0;

    speedX = 3;
}

void Turtle::Update(Player* player, vector<Ground*> grounds)
{
    mask = sprite.getGlobalBounds();
    mask.left += 16;
    mask.width -= 32;
    mask.top += 16;
    mask.height -= 16;

    distance_calculation = player->sprite.getPosition() - sprite.getPosition();;
    if (distance_calculation.x < 0) {distance_calculation.x = -distance_calculation.x;}
    if (distance_calculation.y < 0) {distance_calculation.y = -distance_calculation.y;}

    if (distance_calculation.x > distance_calculation.y)
    {
        distance = distance_calculation.x;
    }
    else
    {
        distance = distance_calculation.y;
    }

    for ( unsigned int i=0; i < grounds.size(); i++ )
    {
        Ground *ground = grounds.at(i);

        sf::FloatRect rect = mask;
        rect.left += speedX;

        if (rect.intersects(ground->sprite.getGlobalBounds()))
        {
            speedX = -speedX;
        }
    }

    sprite.move(sf::Vector2f(speedX, 0));

    ChangeAnimation();
}

void Turtle::ChangeAnimation()
{
    switch (spriteFrame)
    {
        case 0:
        {
            sprite.setTexture(texture1);
        }
        break;
        case 10:
        {
            sprite.setTexture(texture2);
            walkSound.play();
        }
        break;
    }

    spriteFrame += 1;
    if (spriteFrame > 20)
    {
        spriteFrame = 0;
    }

    if (speedX > 0)
    {
        sprite.setScale(sf::Vector2f(1, 1));
    }
    else
    {
        sprite.setScale(sf::Vector2f(-1, 1));
    }
}

void Turtle::SetSoundsVolume(float volume)
{
    walkSound.setVolume( (maxSoundsVolume - distance / maxSoundsDistance * maxSoundsVolume) * volume / 100 );
}

void Turtle::Draw(sf::RenderWindow &window, float cameraX)
{
    sprite.setPosition( sprite.getPosition() - sf::Vector2f(cameraX, 0) );
    window.draw(sprite);
}
