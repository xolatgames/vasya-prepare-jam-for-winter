#ifndef BACK_H
#define BACK_H

#include <SFML/Graphics.hpp>

class BackTexture
{
public:
    BackTexture(int id, float x, float y);

    void Draw(sf::RenderWindow &window, float cameraX);

    enum Image {House, Tree};
    sf::Image image;

    sf::Texture texture;
    sf::Sprite sprite;
};

#endif // BACK_H
