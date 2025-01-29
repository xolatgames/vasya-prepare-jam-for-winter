#ifndef CLOUD_H
#define CLOUD_H

#include <random>
#include <ctime>
#include <SFML/Graphics.hpp>

class Cloud
{
public:
    Cloud(int rand_seed);

    void Update();
    void Draw(sf::RenderWindow &window, float cameraX);

    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    float x;
    float y;
    float speed;

    float leftBorder = -128;
    float rightBorder = 1408;
};

#endif // CLOUD_H
