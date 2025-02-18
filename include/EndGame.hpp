#ifndef END_GAME_H
#define END_GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "background.hpp"

class Background;

class EndGame
{
public:
    EndGame();

    sf::Image endGameImage;
    sf::Texture endGameTexture;
    sf::Sprite endGameSprite;

    Background *background;

    void Draw(sf::RenderWindow &window);
};

#endif // END_GAME_H
