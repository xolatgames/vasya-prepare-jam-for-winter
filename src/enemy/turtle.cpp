#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "../../include/enemy/turtle.hpp"
#include "../../include/ground.hpp"

using namespace std;

Turtle::Turtle(float turtleX, float turtleY)
{
    turtle1Image.loadFromFile("png/enemy/turtle1.png");
    turtle2Image.loadFromFile("png/enemy/turtle2.png");
    turtle1Texture.loadFromImage(turtle1Image);
    turtle2Texture.loadFromImage(turtle2Image);
    turtleSprite.setTexture(turtle1Texture);
    turtleSprite.setOrigin(sf::Vector2f(32, 32));
    turtleSprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    turtleSprite.setPosition(sf::Vector2f(turtleX, turtleY));

    walkBuffer.loadFromFile("sound/walk.wav");
    walkSound.setBuffer(walkBuffer);

    spriteFrame = 0;

    speedX = 3;
}

void Turtle::Update(Player* player, vector<Ground*> grounds)
{
    turtleMask = turtleSprite.getGlobalBounds();
    turtleMask.left += 16;
    turtleMask.width -= 32;
    turtleMask.top += 16;
    turtleMask.height -= 16;

    distance_calculation = player->playerSprite.getPosition() - turtleSprite.getPosition();;
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

        sf::FloatRect turtleRect = turtleMask;
        turtleRect.left += speedX;

        if (turtleRect.intersects(ground->groundSprite.getGlobalBounds()))
        {
            speedX = -speedX;
        }
    }

    turtleSprite.move(sf::Vector2f(speedX, 0));

    ChangeAnimation();
}

void Turtle::ChangeAnimation()
{
    walkSound.setVolume(50 - distance/1280*50);

    switch (spriteFrame)
    {
        case 0:
        {
            turtleSprite.setTexture(turtle1Texture);
        }
        break;
        case 10:
        {
            turtleSprite.setTexture(turtle2Texture);
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
        turtleSprite.setScale(sf::Vector2f(1, 1));
    }
    else
    {
        turtleSprite.setScale(sf::Vector2f(-1, 1));
    }
}

void Turtle::Draw(sf::RenderWindow &window, float cameraX)
{
    turtleSprite.setPosition( turtleSprite.getPosition() - sf::Vector2f(cameraX, 0) );
    window.draw(turtleSprite);
}
