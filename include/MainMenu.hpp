#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "background.hpp"
#include "jam.hpp"

class Background;
class Jam;

class Play
{
public:
    Play();

    sf::Image playImage;
    sf::Texture playTexture;
    sf::Sprite playSprite;

    sf::Image hoverImage;
    sf::Texture hoverTexture;
    sf::Sprite hoverSprite;

    void Hover(sf::RenderWindow &window);
    bool Click(sf::RenderWindow &window);
};

class MainMenu
{
public:
    MainMenu();

    sf::Image labelImage;
    sf::Texture labelTexture;
    sf::Sprite labelSprite;

    Background *background;
    Jam *jam;

    Play *play;

    void Draw(sf::RenderWindow &window);
};

#endif // MAIN_MENU_H
