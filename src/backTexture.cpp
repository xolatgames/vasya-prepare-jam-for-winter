#include <SFML/Graphics.hpp>
#include "../include/backTexture.hpp"

BackTexture::BackTexture(int image, float backX, float backY)
{
    switch (image)
    {
        case BackTexture::House:
        {
            backImage.loadFromFile("png/back/house.png");
            backTexture.loadFromImage(backImage);
            backSprite.setTexture(backTexture);
            backSprite.setOrigin(sf::Vector2f(32, 32));
            backSprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
        }
        break;
        case BackTexture::Tree:
        {
            backImage.loadFromFile("png/back/tree.png");
            backTexture.loadFromImage(backImage);
            backSprite.setTexture(backTexture);
            backSprite.setOrigin(sf::Vector2f(32, 32));
            backSprite.setTextureRect(sf::IntRect(0, 0, 128, 128));
        }
        break;
    }

    backSprite.setPosition(sf::Vector2f(backX, backY));
}

void BackTexture::Draw(sf::RenderWindow &window, float cameraX)
{
    backSprite.setPosition( backSprite.getPosition() - sf::Vector2f(cameraX, 0) );
    window.draw(backSprite);
}
