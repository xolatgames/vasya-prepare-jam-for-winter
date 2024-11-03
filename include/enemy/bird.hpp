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
    Bird(float x, float y);

    void Update(Player* player);
    void SetSoundsVolume(float volume);
    void Draw(sf::RenderWindow &window, float cameraX);

    sf::Image image1;
    sf::Image image2;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Sprite sprite;

    sf::FloatRect mask;

    sf::SoundBuffer wingsBuffer;
    sf::Sound wingsSound;

    const float maxSoundsVolume = 50;
    const float maxSoundsDistance = 1280;

    int spriteFrame;

    bool active;
    const float activate_distance = 640;

    const float speed = 3;

    sf::Vector2f distance_calculation;
    float distance;
    sf::Vector2f direction;

    const float minDistance = 32;

private:
    void ChangeAnimation();
};

#endif // BIRD_H
