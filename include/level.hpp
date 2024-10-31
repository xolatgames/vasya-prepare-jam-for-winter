#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "background.hpp"
#include "backTexture.hpp"
#include "player.hpp"
#include "ground.hpp"
#include "jam.hpp"
#include "enemy/turtle.hpp"
#include "enemy/rabbit.hpp"
#include "enemy/bird.hpp"

using namespace std;

class Background;
class Player;
class Ground;
class Jam;
class Turtle;
class Rabbit;
class Bird;

class Level
{
public:
    Level(string tileMap[], string backMap[], int sizeX, int sizeY);

    Background *background;

    vector<BackTexture*> backTextures;

    Player *player;

    vector<Ground*> grounds;
    vector<Jam*> jams;
    vector<Turtle*> turtles;
    vector<Rabbit*> rabbits;
    vector<Bird*> birds;

    void UI(sf::RenderWindow &window);

    sf::Font font;

    sf::Image jamImage;
    sf::Texture jamTexture;
    sf::Sprite jamSprite;

    sf::Text jamNumber;
};

#endif // LEVEL_H
