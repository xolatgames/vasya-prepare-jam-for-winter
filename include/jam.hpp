#ifndef JAM_H
#define JAM_H

#include <SFML/Graphics.hpp>

class Jam
{
public:
    Jam(float jamX, float JamY);

    void Update();
    void Draw(sf::RenderWindow &window, float cameraX);

    sf::Image jamImage;
    sf::Texture jamTexture;
    sf::Sprite jamSprite;

    sf::FloatRect jamMask;
};

#endif // JAM_H
