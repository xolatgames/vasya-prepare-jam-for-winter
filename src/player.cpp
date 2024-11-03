#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "../include/player.hpp"
#include "../include/ground.hpp"
#include "../include/jam.hpp"
#include "../include/enemy/turtle.hpp"
#include "../include/enemy/rabbit.hpp"
#include "../include/enemy/bird.hpp"

using namespace std;

Player::Player(float playerX, float playerY)
{
    idleImage.loadFromFile("png/player/idle.png");
    walk1Image.loadFromFile("png/player/walk1.png");
    walk2Image.loadFromFile("png/player/walk2.png");
    fallImage.loadFromFile("png/player/fall.png");
    jumpImage.loadFromFile("png/player/jump.png");
    loseImage.loadFromFile("png/player/lose.png");
    idleTexture.loadFromImage(idleImage);
    walk1Texture.loadFromImage(walk1Image);
    walk2Texture.loadFromImage(walk2Image);
    fallTexture.loadFromImage(fallImage);
    jumpTexture.loadFromImage(jumpImage);
    loseTexture.loadFromImage(loseImage);

    sprite.setTexture(idleTexture);
    sprite.setOrigin(sf::Vector2f(32, 32));
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(sf::Vector2f(playerX, playerY));

    walkBuffer.loadFromFile("sound/walk.wav");
    jumpBuffer.loadFromFile("sound/jump.wav");
    jamBuffer.loadFromFile("sound/jam.wav");
    loseBuffer.loadFromFile("sound/lose.wav");
    walkSound.setBuffer(walkBuffer);
    jumpSound.setBuffer(jumpBuffer);
    jamSound.setBuffer(jamBuffer);
    loseSound.setBuffer(loseBuffer);

    side = Side::Right;
    spriteFrame = 0;

    speedX = 0;
    speedY = 0;

    jumpNumber = 0;
    jumpKeyReleased = true;
    jumpTimer = -1;

    lose = false;
}

void Player::Update(vector<Ground*> grounds)
{
    if (!lose)
    {
        mask = sprite.getGlobalBounds();
        mask.left += 16;
        mask.width -= 32;
        mask.top += 16;
        mask.height -= 16;

        Input();

        if (speedX < -decelerationX)
        {
            speedX += decelerationX;
        }
        else if (speedX > decelerationX)
        {
            speedX -= decelerationX;
        }
        else
        {
            speedX = 0;
        }

        if (speedX < -maxSpeedX)
        {
            speedX = -maxSpeedX;
        }
        else if (speedX > maxSpeedX)
        {
            speedX = maxSpeedX;
        }

        speedY += gravityForce;

        if (speedY > maxFallSpeed) { speedY = maxFallSpeed; }

        grounded = false;

        for ( unsigned int i=0; i < grounds.size(); i++ )
        {
            Ground *ground = grounds.at(i);

            sf::FloatRect rect = mask;
            rect.top += speedY;

            if (rect.intersects(ground->sprite.getGlobalBounds()))
            {
                if ( (speedY > 1)||(speedY < -0.5) ) { walkSound.play(); }

                if (speedY > 0)
                {
                    jumpNumber = 2;
                    grounded = true;
                    sprite.setPosition(sf::Vector2f(sprite.getPosition().x, ground->sprite.getGlobalBounds().top - 32));
                    speedY = 0;
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
                speedX = 0;
            }
        }

        sprite.move(sf::Vector2f(speedX, 0));

        if (jumpTimer > 0)
        {
            jumpTimer -= 1;
        }
        else if (jumpTimer == 0)
        {
            Jump();
            jumpTimer = -1;
        }

        ChangeAnimation();

        if ( sprite.getPosition().y > 900 ) { Lose(); }
    }
    else
    {
        speedY += gravityForce;
        sprite.move(sf::Vector2f(0, speedY));
    }
}

void Player::Input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        speedX -= accelerationX;
        side = Side::Left;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        speedX += accelerationX;
        side = Side::Right;
    }

    if ( (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) && (jumpKeyReleased) )
    {
        if (jumpNumber > 0)
        {
            Jump();
        }
        else
        {
            jumpTimer = 6;
        }
        jumpKeyReleased = false;
    }

    if ( !sf::Keyboard::isKeyPressed(sf::Keyboard::Space) )
    {
        jumpKeyReleased = true;
    }
}

void Player::Jump()
{
    if (jumpNumber > 0)
    {
        speedY = -jumpForce;
        jumpSound.play();
        jumpNumber -= 1;
    }
}

void Player::ChangeAnimation()
{
    if (speedY > 0)
    {
        sprite.setTexture(fallTexture);
    }
    else if (speedY < 0)
    {
        sprite.setTexture(jumpTexture);
    }
    else if ( ( speedX < 0 )||( speedX > 0 ) )
    {
        switch (spriteFrame)
        {
            case 0:
            {
                sprite.setTexture(walk1Texture);
                walkSound.play();
            }
            break;
            case 10:
            {
                sprite.setTexture(idleTexture);
            }
            break;
            case 20:
            {
                sprite.setTexture(walk2Texture);
                walkSound.play();
            }
            break;
            case 30:
            {
                sprite.setTexture(idleTexture);
            }
            break;
        }
    }
    else
    {
        sprite.setTexture(idleTexture);
    }

    spriteFrame += 1;
    if (spriteFrame > 40) { spriteFrame = 0; }

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

float Player::Camera()
{
    return sprite.getPosition().x - 640;
}

int Player::PickUpJam(vector<Jam*> jams)
{
    if (!lose)
    {
        for ( unsigned int i=0; i < jams.size(); i++ )
        {
            Jam *jam = jams.at(i);

            if (mask.intersects(jam->mask))
            {
                jamSound.play();
                return i;
            }
        }
    }

    return -1;
}

int Player::ContactWithTurtle(vector<Turtle*> turtles)
{
    if (!lose)
    {
        for ( unsigned int i=0; i < turtles.size(); i++ )
        {
            Turtle *turtle = turtles.at(i);

            sf::FloatRect rect = mask;
            rect.top += speedY + 4;

            if (rect.intersects(turtle->mask))
            {
                if (turtle->active)
                {
                    if ( (speedY > 0)&&(!mask.intersects(turtle->mask)) )
                    {
                        speedY = -push_from_enemy_force;
                        jumpSound.play();
                        jumpNumber = 1;
                        return i;
                    }
                    else { Lose(); }
                }
            }
        }
    }

    return -1;
}

int Player::ContactWithRabbit(vector<Rabbit*> rabbits)
{
    if (!lose)
    {
        for ( unsigned int i=0; i < rabbits.size(); i++ )
        {
            Rabbit *rabbit = rabbits.at(i);

            sf::FloatRect rect = mask;
            rect.top += speedY + 4;

            if (rect.intersects(rabbit->mask))
            {
                if (rabbit->active)
                {
                    if ( (speedY > 0)&&(!mask.intersects(rabbit->mask)) )
                    {
                        speedY = -push_from_enemy_force;
                        jumpSound.play();
                        jumpNumber = 1;
                        return i;
                    }
                    else { Lose(); }
                }
            }
        }
    }

    return -1;
}

int Player::ContactWithBird(vector<Bird*> birds)
{
    if (!lose)
    {
        for ( unsigned int i=0; i < birds.size(); i++ )
        {
            Bird *bird = birds.at(i);

            sf::FloatRect rect = mask;
            rect.top += speedY + 4;

            if (rect.intersects(bird->mask))
            {
                if (bird->active)
                {
                    if ( (speedY > 0)&&(!mask.intersects(bird->mask)) )
                    {
                        speedY = -push_from_enemy_force;
                        jumpSound.play();
                        jumpNumber = 1;
                        return i;
                    }
                    else { Lose(); }
                }
            }
        }
    }

    return -1;
}

void Player::Lose()
{
    speedY = -loseHopForce;
    sprite.setTexture(loseTexture);
    loseSound.play();
    lose = true;
}

bool Player::Restart()
{
    if ( sprite.getPosition().y > 1000 )
    {
        return true;
    }
    return false;
}

void Player::SetSoundsVolume(float volume)
{
    walkSound.setVolume(volume);
    jumpSound.setVolume(volume);
    jamSound.setVolume(volume);
    loseSound.setVolume(volume);
}

void Player::Draw(sf::RenderWindow &window, float cameraX)
{
    sprite.setPosition( sprite.getPosition() - sf::Vector2f(cameraX, 0) );
    window.draw(sprite);
}
