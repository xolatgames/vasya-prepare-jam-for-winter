#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "cloud.hpp"

using namespace std;

class Background
{
public:
    Background();

    void Draw(sf::RenderWindow &window, float cameraX);

    sf::Image backgroundImage;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Image sunImage;
    sf::Texture sunTexture;
    sf::Sprite sunSprite;

    vector<Cloud*> clouds;
};

#endif // BACKGROUND_H
