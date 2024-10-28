#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "ground.hpp"
#include "jam.hpp"

using namespace std;

class Ground;
class Jam;

class Player
{
public:
    Player(float playerX, float playerY);

    void Update(vector<Ground*> grounds);
    float Camera();
    int PickUpJam(vector<Jam*> jams);
    bool Restart();
    void Draw(sf::RenderWindow &window, float cameraX);

    sf::Image idleImage;
    sf::Image walk1Image;
    sf::Image walk2Image;
    sf::Image fallImage;
    sf::Image jumpImage;
    sf::Texture idleTexture;
    sf::Texture walk1Texture;
    sf::Texture walk2Texture;
    sf::Texture fallTexture;
    sf::Texture jumpTexture;
    sf::Sprite playerSprite;

    sf::FloatRect playerMask;

    sf::SoundBuffer walkBuffer;
    sf::SoundBuffer jumpBuffer;
    sf::SoundBuffer jamBuffer;
    sf::Sound walkSound;
    sf::Sound jumpSound;
    sf::Sound jamSound;

    enum Side { Left, Right };
    int side;

    int spriteFrame;

    float speedX;
    float speedY;

    bool grounded;
    int jumpNumber;
    bool jumpKeyReleased;
    int jumpTimer;

private:
    void Input();
    void Jump();
    void ChangeAnimation();
};

#endif // PLAYER_H
