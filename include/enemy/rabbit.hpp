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
    Rabbit(float rabbitX, float rabbitY);

    void Update(Player* player, vector<Ground*> grounds);
    void Draw(sf::RenderWindow &window, float cameraX);

    sf::Image rabbit1Image;
    sf::Image rabbit2Image;
    sf::Texture rabbit1Texture;
    sf::Texture rabbit2Texture;
    sf::Sprite rabbitSprite;

    sf::FloatRect rabbitMask;

    sf::SoundBuffer jumpBuffer;
    sf::Sound jumpSound;

    enum Side { Left, Right };
    int side;

    sf::Vector2f distance_calculation;
    float distance;

    int jump_delay;

    float speedX;
    float speedY;

private:
    void Hop();
    void ChangeAnimation();
};

#endif // RABBIT_H
