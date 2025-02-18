#include "../include/EndGame.hpp"

EndGame::EndGame()
{
    background = new Background();
}

void EndGame::Draw(sf::RenderWindow &window)
{
    endGameImage.loadFromFile("png/end_game.png");
    endGameTexture.loadFromImage(endGameImage);
    endGameSprite.setTexture(endGameTexture);
    endGameSprite.setOrigin(640, 400);
    endGameSprite.setTextureRect(sf::IntRect(0, 0, 1280, 800));
    endGameSprite.setPosition(sf::Vector2f(640, 400));

    window.draw(endGameSprite);
}
