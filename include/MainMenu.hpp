#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "background.hpp"
#include "label.hpp"

class Background;
class Label;

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

    sf::Vector2f cursor_pos;
    sf::Cursor cursor;

    bool Hover(sf::RenderWindow &window);
    bool Click(sf::RenderWindow &window, bool mousePressed);
};

class Slider
{
public:
    Slider(float x, float y);

    sf::Image sliderImage;
    sf::Texture sliderTexture;
    sf::Sprite sliderSprite;

    sf::Image grabberImage;
    sf::Texture grabberTexture;
    sf::Sprite grabberSprite;

    sf::Image grabberHoverImage;
    sf::Texture grabberHoverTexture;
    sf::Sprite grabberHoverSprite;

    sf::Vector2f cursor_pos;
    sf::Cursor cursor;

    bool grab;

    bool Hover(sf::RenderWindow &window);
    float Change(sf::RenderWindow &window, bool mousePressed, bool mouseReleased);
};

class MainMenu
{
public:
    MainMenu();

    sf::Image thumbnailImage;
    sf::Texture thumbnailTexture;
    sf::Sprite thumbnailSprite;

    Background *background;

    Play *play;

    vector<Label*> labels;

    Slider *sounds_slider;
    Slider *music_slider;

    void Draw(sf::RenderWindow &window);
};

#endif // MAIN_MENU_H
