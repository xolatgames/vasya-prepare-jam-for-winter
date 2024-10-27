#include <SFML/Graphics.hpp>
#include "../include/MainMenu.hpp"
#include "../include/background.hpp"

MainMenu::MainMenu()
{
    background = new Background();
    jam = new Jam(992, 96);
    (*jam).jamSprite.setOrigin(64, 64);
    (*jam).jamSprite.setScale(sf::Vector2f(0.5, 0.5));
    (*jam).jamSprite.setRotation(45);

    play = new Play();
}

void MainMenu::Draw(sf::RenderWindow &window)
{
    labelImage.loadFromFile("png/menu/label.png");
    labelTexture.loadFromImage(labelImage);
    labelSprite.setTexture(labelTexture);
    labelSprite.setOrigin(320, 128);
    labelSprite.setTextureRect(sf::IntRect(0, 0, 640, 256));
    labelSprite.setPosition(sf::Vector2f(640, 128));

    window.draw(labelSprite);
    window.draw((*play).playSprite);
    window.draw((*play).hoverSprite);
}

Play::Play()
{
    playImage.loadFromFile("png/menu/play.png");
    playTexture.loadFromImage(playImage);
    playSprite.setTexture(playTexture);
    playSprite.setOrigin(sf::Vector2f(256, 64));
    playSprite.setTextureRect(sf::IntRect(0, 0, 512, 128));
    playSprite.setPosition(sf::Vector2f(640, 400));

    hoverImage.loadFromFile("png/menu/hover_button.png");
    hoverTexture.loadFromImage(hoverImage);
    hoverSprite.setTexture(hoverTexture);
    hoverSprite.setColor(sf::Color(255, 255, 255, 0));
    hoverSprite.setOrigin(playSprite.getOrigin());
    hoverSprite.setTextureRect(playSprite.getTextureRect());
    hoverSprite.setPosition(playSprite.getPosition());
}

void Play::Hover(sf::RenderWindow &window)
{
    sf::Vector2f cursor_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Cursor cursor;

    if ( playSprite.getGlobalBounds().contains(cursor_pos) )
    {
        cursor.loadFromSystem(sf::Cursor::Hand);
        window.setMouseCursor(cursor);
        hoverSprite.setColor(sf::Color(255, 255, 255, 100));
        return;
    }

    cursor.loadFromSystem(sf::Cursor::Arrow);
    window.setMouseCursor(cursor);
    hoverSprite.setColor(sf::Color(255, 255, 255, 0));
}

bool Play::Click(sf::RenderWindow &window)
{
    sf::Vector2f cursor_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    sf::Cursor cursor;

    if ( (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (playSprite.getGlobalBounds().contains(cursor_pos)) )
    {
        cursor.loadFromSystem(sf::Cursor::Arrow);
        window.setMouseCursor(cursor);
        return true;
    }

    return false;
}
