#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../include/enemy/bird.hpp"
#include "../../include/player.hpp"

Bird::Bird(float birdX, float birdY)
{
    bird1Image.loadFromFile("png/enemy/bird1.png");
    bird2Image.loadFromFile("png/enemy/bird2.png");
    bird1Texture.loadFromImage(bird1Image);
    bird2Texture.loadFromImage(bird2Image);
    birdSprite.setTexture(bird1Texture);
    birdSprite.setOrigin(sf::Vector2f(32, 32));
    birdSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    birdSprite.setPosition(sf::Vector2f(birdX, birdY));

    wingsBuffer.loadFromFile("sound/wings.wav");
    wingsSound.setBuffer(wingsBuffer);

    spriteFrame = 0;
}

void Bird::Update(Player* player)
{
    birdMask = birdSprite.getGlobalBounds();
    birdMask.left += 16;
    birdMask.width -= 32;
    birdMask.top += 16;
    birdMask.height -= 32;

    direction = player->playerSprite.getPosition() - birdSprite.getPosition();

    distance_calculation = direction;
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

    direction = direction / distance;

    if (distance > 32)
    {
        birdSprite.move(direction * float(3));
    }

    ChangeAnimation();
}

void Bird::ChangeAnimation()
{
    wingsSound.setVolume(50 - distance/1280*50);

    switch (spriteFrame)
    {
        case 0:
        {
            birdSprite.setTexture(bird1Texture);
        }
        break;
        case 10:
        {
            birdSprite.setTexture(bird2Texture);
            wingsSound.play();
        }
        break;
    }

    spriteFrame += 1;
    if (spriteFrame > 20)
    {
        spriteFrame = 0;
    }

    if (direction.x > 0)
    {
        birdSprite.setScale(sf::Vector2f(1, 1));
    }
    else
    {
        birdSprite.setScale(sf::Vector2f(-1, 1));
    }
}

void Bird::Draw(sf::RenderWindow &window, float cameraX)
{
    birdSprite.setPosition( birdSprite.getPosition() - sf::Vector2f(cameraX, 0) );
    window.draw(birdSprite);
}
