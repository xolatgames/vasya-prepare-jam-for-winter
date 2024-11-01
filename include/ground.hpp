#ifndef GROUND_H
#define GROUND_H

#include <SFML/Graphics.hpp>

class Ground
{
public:
    Ground(int id, float x, float y);

    void Draw(sf::RenderWindow &window, float cameraX);

    enum Image {Top, Center};
    sf::Image image;

    sf::Texture texture;
    sf::Sprite sprite;
};

#endif // GROUND_H
