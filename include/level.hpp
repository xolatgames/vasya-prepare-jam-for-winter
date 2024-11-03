#ifndef LEVEL_H
#define LEVEL_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "background.hpp"
#include "backTexture.hpp"
#include "label.hpp"
#include "player.hpp"
#include "ground.hpp"
#include "jam.hpp"
#include "enemy/turtle.hpp"
#include "enemy/rabbit.hpp"
#include "enemy/bird.hpp"

using namespace std;

class Background;
class Label;
class Player;
class Ground;
class Jam;
class Turtle;
class Rabbit;
class Bird;

class Level
{
public:
    Level(vector<string> backMap, vector<string> labelsMap, vector<string> tileMap, int sizeX, int sizeY);

    Background *background;

    vector<BackTexture*> backTextures;
    vector<Label*> labels;

    Player *player;

    vector<Ground*> grounds;
    vector<Jam*> jams;
    vector<Turtle*> turtles;
    vector<Rabbit*> rabbits;
    vector<Bird*> birds;

    void SetLabelText(int idx, string text);
    void UI(sf::RenderWindow &window);

    sf::Font font;

    sf::Image jamImage;
    sf::Texture jamTexture;
    sf::Sprite jamSprite;

    sf::Text jamNumber;
};

#endif // LEVEL_H
