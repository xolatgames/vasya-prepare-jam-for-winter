#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/level.hpp"
#include "../include/background.hpp"
#include "../include/backTexture.hpp"
#include "../include/player.hpp"
#include "../include/ground.hpp"
#include "../include/jam.hpp"

using namespace std;

Level::Level(string tileMap[], string backMap[], int sizeX, int sizeY)
{
    background = new Background();

    for ( int x=0; x < sizeX; x++ )
        for ( int y=0; y < sizeY; y++ )
        {
            int tile = x + y * sizeX;

            if ( backMap[tile] == "H" )
            {
                backTextures.push_back(new BackTexture(BackTexture::House, x * 64, y * 64 + 64));
            }
            else if ( backMap[tile] == "T" )
            {
                backTextures.push_back(new BackTexture(BackTexture::Tree, x * 64, y * 64 + 64));
            }
        }

    for ( int x=0; x < sizeX; x++ )
        for ( int y=0; y < sizeY; y++ )
        {
            int tile = x + y * sizeX;

            if ( tileMap[tile] == "P" )
            {
                player = new Player(x * 64, y * 64 + 64);
            }
            else if ( tileMap[tile] == "GT" )
            {
                grounds.push_back(new Ground(Ground::Top, x * 64, y * 64 + 64));
            }
            else if ( tileMap[tile] == "G" )
            {
                grounds.push_back(new Ground(Ground::Center, x * 64, y * 64 + 64));
            }
            else if ( tileMap[tile] == "J" )
            {
                jams.push_back(new Jam(x * 64, y * 64 + 64));
            }
        }
}

void Level::UI(sf::RenderWindow &window)
{
    font.loadFromFile("DejaVuSans.ttf");

    jamImage.loadFromFile("png/jam.png");
    jamTexture.loadFromImage(jamImage);
    jamSprite.setTexture(jamTexture);
    jamSprite.setTextureRect(sf::IntRect(0, 0, 256, 256));
    jamSprite.setScale(sf::Vector2f(0.25, 0.25));
    jamSprite.setPosition(sf::Vector2f(8, 8));

    jamNumber.setFont(font);
    jamNumber.setCharacterSize(36);
    jamNumber.setFillColor(sf::Color::White);
    jamNumber.setOutlineColor(sf::Color::Black);
    jamNumber.setOutlineThickness(2);
    jamNumber.setPosition(80, 16);
    jamNumber.setString(to_string(jams.size()));

    window.draw(jamSprite);
    window.draw(jamNumber);
}