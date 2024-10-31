#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "../../include/enemy/rabbit.hpp"
#include "../../include/ground.hpp"

Rabbit::Rabbit(float rabbitX, float rabbitY)
{
    rabbit1Image.loadFromFile("png/enemy/rabbit1.png");
    rabbit2Image.loadFromFile("png/enemy/rabbit2.png");
    rabbit1Texture.loadFromImage(rabbit1Image);
    rabbit2Texture.loadFromImage(rabbit2Image);
    rabbitSprite.setTexture(rabbit1Texture);
    rabbitSprite.setOrigin(sf::Vector2f(32, 32));
    rabbitSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    rabbitSprite.setPosition(sf::Vector2f(rabbitX, rabbitY));
    rabbitSprite.setScale(sf::Vector2f(-1, 1));

    jumpBuffer.loadFromFile("sound/jump.wav");
    jumpSound.setBuffer(jumpBuffer);

    side = Side::Left;

    jump_delay = 60;
}

void Rabbit::Update(Player* player, vector<Ground*> grounds)
{
    rabbitMask = rabbitSprite.getGlobalBounds();
    rabbitMask.left += 16;
    rabbitMask.width -= 32;
    rabbitMask.top += 16;
    rabbitMask.height -= 16;

    distance_calculation = player->playerSprite.getPosition() - rabbitSprite.getPosition();;
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

    speedY += 0.2;

    if (speedY > 8)
    {
        speedY = 8;
    }

    for ( unsigned int i=0; i < grounds.size(); i++ )
    {
        Ground *ground = grounds.at(i);

        sf::FloatRect rabbitRect = rabbitMask;
        rabbitRect.top += speedY;

        if (rabbitRect.intersects(ground->groundSprite.getGlobalBounds()))
        {
            if (speedY > 0)
            {
                rabbitSprite.setPosition(sf::Vector2f(rabbitSprite.getPosition().x, ground->groundSprite.getGlobalBounds().top - 32));
                speedX = 0;
                speedY = 0;

                if (jump_delay < 0)
                {
                    jump_delay = 60;
                }
            }
            else
            {
                speedY = 0;
            }
        }
    }

    rabbitSprite.move(sf::Vector2f(0, speedY));

    for ( unsigned int i=0; i < grounds.size(); i++ )
    {
        Ground *ground = grounds.at(i);

        sf::FloatRect rabbitRect = rabbitMask;
        rabbitRect.left += speedX;

        if (rabbitRect.intersects(ground->groundSprite.getGlobalBounds()))
        {
            speedX = -speedX;

            switch (side)
            {
                case Side::Right:
                {
                    side = Side::Left;
                }
                break;

                case Side::Left:
                {
                    side = Side::Right;
                }
                break;
            }
        }
    }

    rabbitSprite.move(sf::Vector2f(speedX, 0));

    jump_delay -= 1;
    if (jump_delay == 0)
    {
        Hop();
    }

    ChangeAnimation();
}

void Rabbit::Hop()
{
    jumpSound.setVolume(80 - distance/1280*80);
    jumpSound.play();

    switch (side)
    {
        case Side::Right:
        {
            speedX = 4;
        }
        break;

        case Side::Left:
        {
            speedX = -4;
        }
        break;
    }

    speedY = -10;
}

void Rabbit::ChangeAnimation()
{
    if ( (speedX > 0)||(speedX < 0) )
    {
        rabbitSprite.setTexture(rabbit2Texture);
    }
    else
    {
        rabbitSprite.setTexture(rabbit1Texture);
    }

    switch (side)
    {
        case Side::Right:
        {
            rabbitSprite.setScale(sf::Vector2f(1, 1));
        }
        break;

        case Side::Left:
        {
            rabbitSprite.setScale(sf::Vector2f(-1, 1));
        }
        break;
    }
}

void Rabbit::Draw(sf::RenderWindow &window, float cameraX)
{
    rabbitSprite.setPosition( rabbitSprite.getPosition() - sf::Vector2f(cameraX, 0) );
    window.draw(rabbitSprite);
}
