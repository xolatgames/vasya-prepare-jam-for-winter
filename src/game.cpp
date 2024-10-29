#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "../include/game.hpp"
#include "../include/MainMenu.hpp"
#include "../include/level.hpp"
#include "../include/background.hpp"
#include "../include/cloud.hpp"
#include "../include/backTexture.hpp"
#include "../include/player.hpp"
#include "../include/ground.hpp"
#include "../include/jam.hpp"

using namespace std;

Game::Game(sf::RenderWindow &window)
{
    music.openFromFile("music/Sun Shine Loop.ogg");
    music.play();

    clickBuffer.loadFromFile("sound/click.wav");
    clickSound.setBuffer(clickBuffer);

    scene = -1;

    cameraX = 0;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        int scene_to = Update(window, scene, menu, level);

        if ( scene_to != -1 )
        {
            scene = scene_to;

            switch (scene)
            {
                case 0:
                {
                    menu = new MainMenu();
                }
                break;

                case 1:
                {
                    string tileMap[] =
                    {
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "J", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "GT", "GT", "GT", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "J", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "GT", "GT", "GT",
                        "0", "0", "0", "P", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "G", "G", "G",
                        "GT", "GT", "GT", "GT", "GT", "GT", "GT", "GT", "GT", "GT", "GT", "GT", "GT", "GT", "GT", "GT", "GT", "G", "G", "G",
                    };

                    string backMap[] =
                    {
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "H", "0", "0", "0", "0", "0", "T", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                        "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0", "0",
                    };

                    level = new Level(tileMap, backMap, 20, 12);
                }
                break;
            }
        }

        Draw(window, scene, menu, level);

        window.display();
    }
}

int Game::Update(sf::RenderWindow &window, int scene, MainMenu *menu, Level *level)
{
    if (scene == -1)
    {
        return 0;
    }
    else if (scene == 0)
    {
        for ( unsigned int i=0; i < (*menu).background->clouds.size(); i++ )
        {
            (*menu).background->clouds.at(i)->Update();

            (*menu).play->Hover(window);
            if ((*menu).play->Click(window))
            {
                clickSound.play();
                return 1;
            }
        }
    }
    else
    {
        for ( unsigned int i=0; i < (*level).background->clouds.size(); i++ )
        {
            (*level).background->clouds.at(i)->Update();
        }

        (*level).player->Update( (*level).grounds );

        int pick_up_jam = (*level).player->PickUpJam( (*level).jams );

        if ( pick_up_jam != -1 )
        {
            (*level).jams.erase((*level).jams.begin() + pick_up_jam );
        }

        if ((*level).player->Restart())
        {
            return scene;
        }

        for ( unsigned int i=0; i < (*level).jams.size(); i++ )
        {
            (*level).jams.at(i)->Update();
        }

        cameraX = (*level).player->Camera();
    }

    return -1;
}

void Game::Draw(sf::RenderWindow &window, int scene, MainMenu *menu, Level *level)
{
    if (scene == 0)
    {
        (*menu).background->Draw(window, 0);
        (*menu).jam->Draw(window, 0);
        (*menu).Draw(window);
    }
    else
    {
        (*level).background->Draw(window, cameraX);

        for ( unsigned int i=0; i < (*level).backTextures.size(); i++ )
        {
            (*level).backTextures.at(i)->Draw(window, cameraX);
        }

        for ( unsigned int i=0; i < (*level).grounds.size(); i++ )
        {
            (*level).grounds.at(i)->Draw(window, cameraX);
        }
        for ( unsigned int i=0; i < (*level).jams.size(); i++ )
        {
            (*level).jams.at(i)->Draw(window, cameraX);
        }

        (*level).player->Draw(window, cameraX);

        (*level).UI(window);
    }
}
