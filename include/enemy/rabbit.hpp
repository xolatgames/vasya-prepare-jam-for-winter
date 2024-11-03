#ifndef RABBIT_H
#define RABBIT_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "../player.hpp"
#include "../ground.hpp"

using namespace std;

class Player;
class Ground;

class Rabbit
{
public:
    Rabbit(float x, float y);

    void Update(Player* player, vector<Ground*> grounds);
    void SetSoundsVolume(float volume);
    void Draw(sf::RenderWindow &window, float cameraX);

    sf::Image idleImage;
    sf::Image jumpImage;
    sf::Texture idleTexture;
    sf::Texture jumpTexture;
    sf::Sprite sprite;

    sf::FloatRect mask;

    sf::SoundBuffer jumpBuffer;
    sf::Sound jumpSound;

    const float maxSoundsVolume = 50;
    const float maxSoundsDistance = 1280;

    enum Side { Left, Right };
    int side;

    bool active;
    const float activate_distance = 640;

    int jump_timer;

    const int jump_delay = 60;

    float speedX;
    float speedY;

    const float jumpForceX = 4;
    const float jumpForceY = 10;
    const float gravityForce = 0.2;
    const float maxFallSpeed = 12;

    sf::Vector2f distance_calculation;
    float distance;

private:
    void Hop();
    void ChangeAnimation();
};

#endif // RABBIT_H
