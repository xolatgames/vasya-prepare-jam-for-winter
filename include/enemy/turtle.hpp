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
    Turtle(float x, float y);

    void Update(Player* player, vector<Ground*> grounds);
    void SetSoundsVolume(float volume);
    void Draw(sf::RenderWindow &window, float cameraX);

    sf::Image image1;
    sf::Image image2;
    sf::Texture texture1;
    sf::Texture texture2;
    sf::Sprite sprite;

    sf::FloatRect mask;

    sf::SoundBuffer walkBuffer;
    sf::Sound walkSound;

    const float maxSoundsVolume = 50;
    const float maxSoundsDistance = 1280;

    int spriteFrame;

    bool active;
    const float activate_distance = 640;

    float speedX;
    float speedY;

    const float gravityForce = 0.2;
    const float maxFallSpeed = 8;

    bool bottom_empty;

    sf::Vector2f distance_calculation;
    float distance;

private:
    void ChangeAnimation();
};

#endif // TURTLE_H
