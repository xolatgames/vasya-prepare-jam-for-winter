#ifndef GROUND_H
#define GROUND_H

#include <SFML/Graphics.hpp>

class Ground
{
public:
    Ground(int image, float groundX, float groundY);

    void Draw(sf::RenderWindow &window, float cameraX);

    enum Image {Top, Center};
    sf::Image groundImage;

    sf::Texture groundTexture;
    sf::Sprite groundSprite;
};

#endif // GROUND_H
