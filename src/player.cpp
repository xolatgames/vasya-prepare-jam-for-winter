#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "../include/player.hpp"
#include "../include/ground.hpp"
#include "../include/jam.hpp"

using namespace std;

Player::Player(float playerX, float playerY)
{
    idleImage.loadFromFile("png/player/idle.png");
    walk1Image.loadFromFile("png/player/walk1.png");
    walk2Image.loadFromFile("png/player/walk2.png");
    fallImage.loadFromFile("png/player/fall.png");
    jumpImage.loadFromFile("png/player/jump.png");
    idleTexture.loadFromImage(idleImage);
    walk1Texture.loadFromImage(walk1Image);
    walk2Texture.loadFromImage(walk2Image);
    fallTexture.loadFromImage(fallImage);
    jumpTexture.loadFromImage(jumpImage);

    playerSprite.setTexture(idleTexture);
    playerSprite.setOrigin(sf::Vector2f(32, 32));
    playerSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    playerSprite.setPosition(sf::Vector2f(playerX, playerY));

    walkBuffer.loadFromFile("sound/walk.wav");
    jumpBuffer.loadFromFile("sound/jump.wav");
    jamBuffer.loadFromFile("sound/jam.wav");
    walkSound.setBuffer(walkBuffer);
    jumpSound.setBuffer(jumpBuffer);
    jamSound.setBuffer(jamBuffer);

    side = Side::Right;
    spriteFrame = 0;

    speedX = 0;
    speedY = 0;

    jumpNumber = 0;
    jumpKeyReleased = true;
    jumpTimer = -1;
}

void Player::Update(vector<Ground*> grounds)
{
    if (speedX < -0.2)
    {
        speedX += 0.1;
    }
    else if (speedX > 0.2)
    {
        speedX -= 0.1;
    }
    else
    {
        speedX = 0;
    }

    if (speedX < -6)
    {
        speedX = -6;
    }
    else if (speedX > 6)
    {
        speedX = 6;
    }

    speedY += 0.2;

    if (speedY > 8)
    {
        speedY = 8;
    }

    Input();

    grounded = false;

    for ( unsigned int i=0; i < grounds.size(); i++ )
    {
        Ground *ground = grounds.at(i);

        sf::FloatRect playerRect = playerSprite.getGlobalBounds();
        playerRect.left += 16;
        playerRect.width -= 32;
        playerRect.top += speedY + 16;
        playerRect.height -= 16;

        if (playerRect.intersects(ground->groundSprite.getGlobalBounds()))
        {
            if ( (speedY > 1)||(speedY < -0.5) )
            {
                walkSound.play();
            }
            if (speedY > 0)
            {
                jumpNumber = 2;
                grounded = true;
                playerSprite.setPosition(sf::Vector2f(playerSprite.getPosition().x, ground->groundSprite.getGlobalBounds().top - 32));
                speedY = 0;
            }
            else
            {
                speedY = 0;
            }
        }
    }

    playerSprite.move(sf::Vector2f(0, speedY));

    for ( unsigned int i=0; i < grounds.size(); i++ )
    {
        Ground *ground = grounds.at(i);

        sf::FloatRect playerRect = playerSprite.getGlobalBounds();
        playerRect.left += speedX + 16;
        playerRect.width -= 32;
        playerRect.top += 16;
        playerRect.height -= 16;

        if (playerRect.intersects(ground->groundSprite.getGlobalBounds()))
        {
            speedX = 0;
        }
    }

    playerSprite.move(sf::Vector2f(speedX, 0));

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
}

void Player::Input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        speedX -= 0.2;
        side = Side::Left;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        speedX += 0.2;
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
        speedY = -8;
        jumpSound.play();
        jumpNumber -= 1;
    }
}

void Player::ChangeAnimation()
{
    if (speedY > 0)
    {
        playerSprite.setTexture(fallTexture);
    }
    else if (speedY < 0)
    {
        playerSprite.setTexture(jumpTexture);
    }
    else if ( ( speedX < 0 )||( speedX > 0 ) )
    {
        switch (spriteFrame)
        {
            case 0:
            {
                playerSprite.setTexture(walk1Texture);
                walkSound.play();
            }
            break;
            case 10:
            {
                playerSprite.setTexture(idleTexture);
            }
            break;
            case 20:
            {
                playerSprite.setTexture(walk2Texture);
                walkSound.play();
            }
            break;
            case 30:
            {
                playerSprite.setTexture(idleTexture);
            }
            break;
        }
    }
    else
    {
        playerSprite.setTexture(idleTexture);
    }

    spriteFrame += 1;
    if (spriteFrame > 40)
    {
        spriteFrame = 0;
    }

    switch (side)
    {
        case Side::Right:
        {
            playerSprite.setScale(sf::Vector2f(1, 1));
        }
        break;

        case Side::Left:
        {
            playerSprite.setScale(sf::Vector2f(-1, 1));
        }
        break;
    }
}

float Player::Camera()
{
    return playerSprite.getPosition().x - 640;
}

int Player::PickUpJam(vector<Jam*> jams)
{
    for ( unsigned int i=0; i < jams.size(); i++ )
    {
        Jam *jam = jams.at(i);

        sf::FloatRect playerRect = playerSprite.getGlobalBounds();
        playerRect.left += 30;
        playerRect.width -= 60;
        playerRect.top += 32;
        playerRect.height -= 32;

        if (playerRect.intersects(jam->jamSprite.getGlobalBounds()))
        {
            jamSound.play();
            return i;
        }
    }
    return -1;
}

bool Player::Restart()
{
    if ( playerSprite.getPosition().y > 900 )
    {
        return true;
    }
    return false;
}

void Player::Draw(sf::RenderWindow &window, float cameraX)
{
    playerSprite.setPosition( playerSprite.getPosition() - sf::Vector2f(cameraX, 0) );
    window.draw(playerSprite);
}
