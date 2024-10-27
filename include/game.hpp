#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "MainMenu.hpp"
#include "level.hpp"
#include "background.hpp"
#include "cloud.hpp"
#include "backTexture.hpp"
#include "player.hpp"
#include "ground.hpp"
#include "jam.hpp"

class Game
{
public:
    Game(sf::RenderWindow &window);
    sf::Event event;

    sf::Music music;
    sf::SoundBuffer clickBuffer;
    sf::Sound clickSound;

    int scene;

    MainMenu *menu;
    Level *level;

    float cameraX;

private:
    int Update(sf::RenderWindow &window, int scene, MainMenu *menu, Level *level);
    void Draw(sf::RenderWindow &window, int scene, MainMenu *menu, Level *level);
};

#endif // GAME_H
