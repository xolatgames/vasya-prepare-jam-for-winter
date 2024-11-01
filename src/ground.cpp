#include <SFML/Graphics.hpp>
#include "../include/ground.hpp"

Ground::Ground(int id, float x, float y)
{
    switch (id)
    {
        case Image::Top:
        {
            image.loadFromFile("png/ground_top.png");
        }
        break;

        case Image::Center:
        {
            image.loadFromFile("png/ground.png");
        }
        break;
    }

    texture.loadFromImage(image);

    sprite.setTexture(texture);
    sprite.setOrigin(sf::Vector2f(32, 32));
    sprite.setTextureRect(sf::IntRect(0, 0, 64, 64));
    sprite.setPosition(sf::Vector2f(x, y));
}

void Ground::Draw(sf::RenderWindow &window, float cameraX)
{
    sprite.setPosition( sprite.getPosition() - sf::Vector2f(cameraX, 0) );
    window.draw(sprite);
}
