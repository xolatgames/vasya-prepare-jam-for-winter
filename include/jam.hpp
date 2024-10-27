#ifndef JAM_H
#define JAM_H

#include <SFML/Graphics.hpp>

class Jam
{
public:
    Jam(float jamX, float JamY);

    void Draw(sf::RenderWindow &window, float cameraX);

    sf::Image jamImage;
    sf::Texture jamTexture;
    sf::Sprite jamSprite;
};

#endif // JAM_H
