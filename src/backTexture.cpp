#include "../include/backTexture.hpp"

BackTexture::BackTexture(int id, float x, float y)
{
    switch (id)
    {
        case BackTexture::House:
        {
            image.loadFromFile("png/back/house.png");
            texture.loadFromImage(image);
            sprite.setTexture(texture);
            sprite.setOrigin(sf::Vector2f(32, 32));
            sprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
        }
        break;
        case BackTexture::Tree:
        {
            image.loadFromFile("png/back/tree.png");
            texture.loadFromImage(image);
            sprite.setTexture(texture);
            sprite.setOrigin(sf::Vector2f(32, 32));
            sprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
        }
        break;
    }

    sprite.setPosition(sf::Vector2f(x, y));
}

void BackTexture::Draw(sf::RenderWindow &window, float cameraX)
{
    sprite.setPosition( sprite.getPosition() - sf::Vector2f(cameraX, 0) );
    window.draw(sprite);
}
