#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "../include/game.hpp"
#include "../include/MainMenu.hpp"
#include "../include/MapParser.hpp"
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
    testBuffer.loadFromFile("sound/jump.wav");
    clickSound.setBuffer(clickBuffer);
    testSound.setBuffer(testBuffer);

    scene = -1;

    soundsVolume = 100;
    test_sound_delay = 0;

    cameraX = 0;

    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            mousePressed = false;
            mouseReleased = false;

            if (event.type == sf::Event::MouseButtonPressed)
            {
                mousePressed = true;
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                mouseReleased = true;
            }
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        if (music.getStatus() == sf::Music::Stopped) { music.play(); }

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
                    mapFile = new MapFile("maps/level1.tmx");

                    mapWidth = mapFile->FindMapWidth();
                    mapHeight = mapFile->FindMapHeight();

                    backMap = mapFile->GetTiles("Back", "0");
                    labelMap = mapFile->GetTiles("Labels", "0");
                    tileMap = mapFile->GetTiles("Objects", "G");

                    cameraX = 0;

                    level = new Level(backMap, labelMap, tileMap, mapWidth, mapHeight);

                    (*level).SetLabelText(0, "Press arrow keys for moving character.");
                    (*level).SetLabelText(1, "You can jump by pressing Space.");
                    (*level).SetLabelText(2, "You can do this twice!");
                    (*level).SetLabelText(3, "If you jump on an enemy head, you defeat it.\notherwise you'll lose!");
                    (*level).SetLabelText(4, "Collect all jams on the level\nfor going to a next level!");
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
        }

        bool ui_hovered = false;

        if ( (*menu).play->Hover(window) ) { ui_hovered = true; }
        if ((*menu).play->Click(window, mousePressed))
        {
            clickSound.play();
            return 1;
        }

        if ( (*menu).sounds_slider->Hover(window) ) { ui_hovered = true; }

        if ( (*menu).sounds_slider->Change(window, mousePressed, mouseReleased) != -1 )
        {
            soundsVolume = (*menu).sounds_slider->Change(window, mousePressed, mouseReleased) / 512 * 100;
            if (test_sound_delay < 0)
            {
                testSound.setVolume(soundsVolume);
                clickSound.setVolume(soundsVolume);
                testSound.play();
                test_sound_delay = 30;
            }
        }

        test_sound_delay -= 1;

        if ( (*menu).music_slider->Hover(window) ) { ui_hovered = true; }
        music.setVolume( (*menu).music_slider->Change(window, mousePressed, mouseReleased) / 512 * 100 );

        if (!ui_hovered)
        {
            sf::Cursor cursor;
            cursor.loadFromSystem(sf::Cursor::Arrow);
            window.setMouseCursor(cursor);
        }
    }
    else
    {
        for ( unsigned int i=0; i < (*level).background->clouds.size(); i++ )
        {
            (*level).background->clouds.at(i)->Update();
        }

        (*level).player->Update( (*level).grounds );
        cameraX = (*level).player->Camera();
        (*level).player->SetSoundsVolume(soundsVolume);

        for ( unsigned int i=0; i < (*level).jams.size(); i++ )
        {
            (*level).jams.at(i)->Update();
        }
        for ( unsigned int i=0; i < (*level).turtles.size(); i++ )
        {
            (*level).turtles.at(i)->Update( (*level).player, (*level).grounds );
            (*level).turtles.at(i)->SetSoundsVolume(soundsVolume);
        }
        for ( unsigned int i=0; i < (*level).rabbits.size(); i++ )
        {
            (*level).rabbits.at(i)->Update( (*level).player, (*level).grounds );
            (*level).rabbits.at(i)->SetSoundsVolume(soundsVolume);
        }
        for ( unsigned int i=0; i < (*level).birds.size(); i++ )
        {
            (*level).birds.at(i)->Update( (*level).player );
            (*level).birds.at(i)->SetSoundsVolume(soundsVolume);
        }

        int pick_up_jam = (*level).player->PickUpJam( (*level).jams );
        if ( pick_up_jam != -1 )
        {
            (*level).jams.erase((*level).jams.begin() + pick_up_jam );
        }

        int contacted_turtle = (*level).player->ContactWithTurtle( (*level).turtles );
        if ( contacted_turtle != -1 )
        {
            (*level).turtles.erase((*level).turtles.begin() + contacted_turtle );
        }

        int contacted_rabbit = (*level).player->ContactWithRabbit( (*level).rabbits );
        if ( contacted_rabbit != -1 )
        {
            (*level).rabbits.erase((*level).rabbits.begin() + contacted_rabbit );
        }

        int contacted_bird = (*level).player->ContactWithBird( (*level).birds );
        if ( contacted_bird != -1 )
        {
            (*level).birds.erase((*level).birds.begin() + contacted_bird );
        }

        if ((*level).player->Restart())
        {
            return scene;
        }
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
        for ( unsigned int i=0; i < (*level).labels.size(); i++ )
        {
            (*level).labels.at(i)->Draw(window, cameraX);
        }

        for ( unsigned int i=0; i < (*level).grounds.size(); i++ )
        {
            (*level).grounds.at(i)->Draw(window, cameraX);
        }
        for ( unsigned int i=0; i < (*level).jams.size(); i++ )
        {
            (*level).jams.at(i)->Draw(window, cameraX);
        }
        for ( unsigned int i=0; i < (*level).turtles.size(); i++ )
        {
            (*level).turtles.at(i)->Draw(window, cameraX);
        }
        for ( unsigned int i=0; i < (*level).rabbits.size(); i++ )
        {
            (*level).rabbits.at(i)->Draw(window, cameraX);
        }
        for ( unsigned int i=0; i < (*level).birds.size(); i++ )
        {
            (*level).birds.at(i)->Draw(window, cameraX);
        }

        (*level).player->Draw(window, cameraX);

        (*level).UI(window);
    }
}
