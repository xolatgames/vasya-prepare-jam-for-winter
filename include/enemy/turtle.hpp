#ifndef TURTLE_H
#define TURTLE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "../player.hpp"
#include "../ground.hpp"

using namespace std;

class Player;
class Ground;

class Turtle
{
public:
    Turtle(float turtleX, float turtleY);

    void Update(Player* player, vector<Ground*> grounds);
    void Draw(sf::RenderWindow &window, float cameraX);

    sf::Image turtle1Image;
    sf::Image turtle2Image;
    sf::Texture turtle1Texture;
    sf::Texture turtle2Texture;
    sf::Sprite turtleSprite;

    sf::FloatRect turtleMask;

    sf::SoundBuffer walkBuffer;
    sf::Sound walkSound;

    int spriteFrame;

    sf::Vector2f distance_calculation;
    float distance;

    float speedX;

private:
    void ChangeAnimation();
};

#endif // TURTLE_H
