#include <SFML/Graphics.hpp>
#include "../include/game.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 800), "Vasya prepare jam for winter!");
    window.setFramerateLimit(60);

    Game game(window);
    return 0;
}
