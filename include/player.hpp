#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "ground.hpp"
#include "jam.hpp"
#include "enemy/turtle.hpp"
#include "enemy/rabbit.hpp"
#include "enemy/bird.hpp"

using namespace std;

class Ground;
class Jam;
class Turtle;
class Rabbit;
class Bird;

class Player
{
public:
    Player(float x, float y);

    void Update(vector<Ground*> grounds);
    float Camera();
    int PickUpJam(vector<Jam*> jams);
    int ContactWithTurtle(vector<Turtle*> turtles);
    int ContactWithRabbit(vector<Rabbit*> rabbits);
    int ContactWithBird(vector<Bird*> birds);
    bool Restart();
    void SetSoundsVolume(float volume);
    void Draw(sf::RenderWindow &window, float cameraX);

    sf::Image idleImage;
    sf::Image walk1Image;
    sf::Image walk2Image;
    sf::Image fallImage;
    sf::Image jumpImage;
    sf::Image loseImage;
    sf::Texture idleTexture;
    sf::Texture walk1Texture;
    sf::Texture walk2Texture;
    sf::Texture fallTexture;
    sf::Texture jumpTexture;
    sf::Texture loseTexture;
    sf::Sprite sprite;

    sf::FloatRect mask;

    sf::SoundBuffer walkBuffer;
    sf::SoundBuffer jumpBuffer;
    sf::SoundBuffer jamBuffer;
    sf::SoundBuffer loseBuffer;
    sf::Sound walkSound;
    sf::Sound jumpSound;
    sf::Sound jamSound;
    sf::Sound loseSound;

    enum Side { Left, Right };
    int side;

    int spriteFrame;

    float speedX;
    float speedY;

    const float accelerationX = 0.2;
    const float decelerationX = 0.1;
    const float maxSpeedX = 6;
    const float gravityForce = 0.2;
    const float maxFallSpeed = 8;
    const float jumpForce = 8;

    bool grounded;
    int jumpNumber;
    bool jumpKeyReleased;
    int jumpTimer;

    const float push_from_enemy_force = 6;

    bool lose;
    const float loseHopForce = 12;

private:
    void Input();
    void Jump();
    void ChangeAnimation();
    void Lose();
};

#endif // PLAYER_H
