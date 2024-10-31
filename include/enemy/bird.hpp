#ifndef BIRD_H
#define BIRD_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../../include/player.hpp"

using namespace std;

class Player;

class Bird
{
public:
    Bird(float birdX, float birdY);

    void Update(Player* player);
    void Draw(sf::RenderWindow &window, float cameraX);

    sf::Image bird1Image;
    sf::Image bird2Image;
    sf::Texture bird1Texture;
    sf::Texture bird2Texture;
    sf::Sprite birdSprite;

    sf::FloatRect birdMask;

    sf::SoundBuffer wingsBuffer;
    sf::Sound wingsSound;

    int spriteFrame;

    sf::Vector2f distance_calculation;
    float distance;
    sf::Vector2f direction;

private:
    void ChangeAnimation();
};

#endif // BIRD_H
