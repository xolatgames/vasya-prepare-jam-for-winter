#ifndef CLOUD_H
#define CLOUD_H

#include <SFML/Graphics.hpp>

class Cloud
{
public:
    Cloud(int rand_seed);

    void Update();
    void Draw(sf::RenderWindow &window, float cameraX);

    sf::Image cloudImage;
    sf::Texture cloudTexture;
    sf::Sprite cloudSprite;

    float cloudX;
    float cloudY;
    float cloudSpeed;
};

#endif // CLOUD_H
