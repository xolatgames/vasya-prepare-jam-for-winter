#ifndef BACK_H
#define BACK_H

#include <SFML/Graphics.hpp>

class BackTexture
{
public:
    BackTexture(int image, float backX, float backY);

    void Draw(sf::RenderWindow &window, float cameraX);

    enum Image {House, Tree};
    sf::Image backImage;

    sf::Texture backTexture;
    sf::Sprite backSprite;
};

#endif // BACK_H
