#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "background.hpp"
#include "backTexture.hpp"
#include "player.hpp"
#include "ground.hpp"
#include "jam.hpp"

using namespace std;

class Background;
class Player;
class Ground;
class Jam;

class Level
{
public:
    Level(string tileMap[], string backMap[], int sizeX, int sizeY);

    Background *background;

    vector<BackTexture*> backTextures;

    Player *player;

    vector<Ground*> grounds;
    vector<Jam*> jams;

    void UI(sf::RenderWindow &window);

    sf::Font font;

    sf::Image jamImage;
    sf::Texture jamTexture;
    sf::Sprite jamSprite;

    sf::Text jamNumber;
};

#endif // LEVEL_H
