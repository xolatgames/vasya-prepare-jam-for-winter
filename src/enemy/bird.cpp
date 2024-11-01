#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../include/enemy/bird.hpp"
#include "../../include/player.hpp"

Bird::Bird(float x, float y)
{
    image1.loadFromFile("png/enemy/bird1.png");
    image2.loadFromFile("png/enemy/bird2.png");
    texture1.loadFromImage(image1);
    texture2.loadFromImage(image2);
    sprite.setTexture(texture1);
    sprite.setOrigin(sf::Vector2f(32, 32));
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(sf::Vector2f(x, y));

    wingsBuffer.loadFromFile("sound/wings.wav");
    wingsSound.setBuffer(wingsBuffer);

    spriteFrame = 0;
}

void Bird::Update(Player* player)
{
    mask = sprite.getGlobalBounds();
    mask.left += 16;
    mask.width -= 32;
    mask.top += 16;
    mask.height -= 32;

    direction = player->sprite.getPosition() - sprite.getPosition();

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

    if (distance > minDistance)
    {
        sprite.move(direction * speed);
    }

    ChangeAnimation();
}

void Bird::ChangeAnimation()
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
        sprite.setScale(sf::Vector2f(1, 1));
    }
    else
    {
        sprite.setScale(sf::Vector2f(-1, 1));
    }
}

void Bird::SetSoundsVolume(float volume)
{
    wingsSound.setVolume( (maxSoundsVolume - distance / maxSoundsDistance * maxSoundsVolume) * volume / 100 );
}

void Bird::Draw(sf::RenderWindow &window, float cameraX)
{
    sprite.setPosition( sprite.getPosition() - sf::Vector2f(cameraX, 0) );
    window.draw(sprite);
}
