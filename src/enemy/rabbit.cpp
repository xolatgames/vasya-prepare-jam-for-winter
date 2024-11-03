#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "../../include/enemy/rabbit.hpp"
#include "../../include/ground.hpp"

Rabbit::Rabbit(float x, float y)
{
    idleImage.loadFromFile("png/enemy/rabbit1.png");
    jumpImage.loadFromFile("png/enemy/rabbit2.png");
    idleTexture.loadFromImage(idleImage);
    jumpTexture.loadFromImage(jumpImage);
    sprite.setTexture(idleTexture);
    sprite.setOrigin(sf::Vector2f(32, 32));
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(sf::Vector2f(x, y));
    sprite.setScale(sf::Vector2f(-1, 1));

    jumpBuffer.loadFromFile("sound/jump.wav");
    jumpSound.setBuffer(jumpBuffer);

    side = Side::Left;

    active = false;

    jump_timer = jump_delay;
}

void Rabbit::Update(Player* player, vector<Ground*> grounds)
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

    if ( distance < activate_distance ) { active = true; }

    speedY += gravityForce;

    if (speedY > maxFallSpeed) { speedY = maxFallSpeed; }

    for ( unsigned int i=0; i < grounds.size(); i++ )
    {
        Ground *ground = grounds.at(i);

        sf::FloatRect rect = mask;
        rect.top += speedY;

        if (rect.intersects(ground->sprite.getGlobalBounds()))
        {
            if (speedY > 0)
            {
                sprite.setPosition(sf::Vector2f(sprite.getPosition().x, ground->sprite.getGlobalBounds().top - 32));
                speedX = 0;
                speedY = 0;

                if (jump_timer < 0)
                {
                    jump_timer = jump_delay;
                }
            }
            else
            {
                speedY = 0;
            }
        }
    }

    sprite.move(sf::Vector2f(0, speedY));

    for ( unsigned int i=0; i < grounds.size(); i++ )
    {
        Ground *ground = grounds.at(i);

        sf::FloatRect rect = mask;
        rect.left += speedX;

        if (rect.intersects(ground->sprite.getGlobalBounds()))
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

    sprite.move(sf::Vector2f(speedX, 0));

    if (active) { jump_timer -= 1; }
    if (jump_timer == 0) { Hop(); }

    ChangeAnimation();
}

void Rabbit::Hop()
{
    jumpSound.play();

    switch (side)
    {
        case Side::Right:
        {
            speedX = jumpForceX;
        }
        break;

        case Side::Left:
        {
            speedX = -jumpForceX;
        }
        break;
    }

    speedY = -jumpForceY;
}

void Rabbit::ChangeAnimation()
{
    if ( (speedX > 0)||(speedX < 0) )
    {
        sprite.setTexture(jumpTexture);
    }
    else
    {
        sprite.setTexture(idleTexture);
    }

    switch (side)
    {
        case Side::Right:
        {
            sprite.setScale(sf::Vector2f(1, 1));
        }
        break;

        case Side::Left:
        {
            sprite.setScale(sf::Vector2f(-1, 1));
        }
        break;
    }
}

void Rabbit::SetSoundsVolume(float volume)
{
    jumpSound.setVolume( (maxSoundsVolume - distance / maxSoundsDistance * maxSoundsVolume) * volume / 100 );
}

void Rabbit::Draw(sf::RenderWindow &window, float cameraX)
{
    sprite.setPosition( sprite.getPosition() - sf::Vector2f(cameraX, 0) );
    window.draw(sprite);
}
