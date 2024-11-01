#ifndef JAM_H
#define JAM_H

#include <SFML/Graphics.hpp>

class Jam
{
public:
    Jam(float x, float y);

    void Update();
    void Draw(sf::RenderWindow &window, float cameraX);

    sf::Image image;
    sf::Texture texture;
    sf::Sprite sprite;

    sf::FloatRect mask;
};

#endif // JAM_H
