#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "MainMenu.hpp"
#include "MapFile.hpp"
#include "level.hpp"
#include "background.hpp"
#include "cloud.hpp"
#include "backTexture.hpp"
#include "player.hpp"
#include "ground.hpp"
#include "jam.hpp"
#include "EndGame.hpp"

using namespace std;

class Game
{
public:
    Game(sf::RenderWindow &window);
    sf::Event event;

    sf::Music music;
    sf::SoundBuffer clickBuffer;
    sf::SoundBuffer testBuffer;
    sf::Sound clickSound;
    sf::Sound testSound;

    int scene;

    bool mousePressed;
    bool mouseReleased;

    float soundsVolume;
    int test_sound_delay;

    MainMenu *menu;
    MapFile *mapFile;
    Level *level;
    EndGame *endGame;

    float cameraX;

    int current_level;

private:
    int Update(sf::RenderWindow &window, int scene, MainMenu *menu, Level *level, EndGame *endGame);
    void Draw(sf::RenderWindow &window, int scene, MainMenu *menu, Level *level, EndGame *endGame);
};

#endif // GAME_H
