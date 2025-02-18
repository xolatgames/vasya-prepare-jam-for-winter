#include "../include/MainMenu.hpp"

MainMenu::MainMenu()
{
    background = new Background();

    play = new Play();

    labels.push_back(new Label("Sounds: ", 352, 496));
    labels.push_back(new Label("Music: ", 352, 560));

    for ( unsigned int i=0; i < labels.size(); i++ )
    {
        labels.at(i)->label.setCharacterSize(24);
    }

    sounds_slider = new Slider(480, 512);
    music_slider = new Slider(480, 576);
}

void MainMenu::Draw(sf::RenderWindow &window)
{
    thumbnailImage.loadFromFile("png/menu/thumbnail.png");
    thumbnailTexture.loadFromImage(thumbnailImage);
    thumbnailSprite.setTexture(thumbnailTexture);
    thumbnailSprite.setOrigin(640, 400);
    thumbnailSprite.setTextureRect(sf::IntRect(0, 0, 1280, 800));
    thumbnailSprite.setPosition(sf::Vector2f(640, 400));

    window.draw(thumbnailSprite);
    window.draw((*play).playSprite);
    window.draw((*play).hoverSprite);

    for ( unsigned int i=0; i < labels.size(); i++ )
    {
        labels.at(i)->Draw(window, 0);
    }

    window.draw(sounds_slider->sliderSprite);
    window.draw(sounds_slider->grabberSprite);
    window.draw(sounds_slider->grabberHoverSprite);

    window.draw(music_slider->sliderSprite);
    window.draw(music_slider->grabberSprite);
    window.draw(music_slider->grabberHoverSprite);
}

Play::Play()
{
    playImage.loadFromFile("png/menu/play.png");
    playTexture.loadFromImage(playImage);
    playSprite.setTexture(playTexture);
    playSprite.setOrigin(sf::Vector2f(256, 64));
    playSprite.setTextureRect(sf::IntRect(0, 0, 512, 128));
    playSprite.setPosition(sf::Vector2f(640, 400));

    hoverImage.loadFromFile("png/menu/hover_button.png");
    hoverTexture.loadFromImage(hoverImage);
    hoverSprite.setTexture(hoverTexture);
    hoverSprite.setColor(sf::Color(255, 255, 255, 0));
    hoverSprite.setOrigin(playSprite.getOrigin());
    hoverSprite.setTextureRect(playSprite.getTextureRect());
    hoverSprite.setPosition(playSprite.getPosition());
}

bool Play::Hover(sf::RenderWindow &window)
{
    cursor_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if ( playSprite.getGlobalBounds().contains(cursor_pos) )
    {
        cursor.loadFromSystem(sf::Cursor::Hand);
        window.setMouseCursor(cursor);
        hoverSprite.setColor(sf::Color(255, 255, 255, 100));
        return true;
    }

    hoverSprite.setColor(sf::Color(255, 255, 255, 0));
    return false;
}

bool Play::Click(sf::RenderWindow &window, bool mousePressed)
{
    cursor_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (mousePressed)
    {
        if ( (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (playSprite.getGlobalBounds().contains(cursor_pos)) )
        {
            cursor.loadFromSystem(sf::Cursor::Arrow);
            window.setMouseCursor(cursor);
            return true;
        }
    }

    return false;
}

Slider::Slider(float x, float y)
{
    sliderImage.loadFromFile("png/menu/slider.png");
    grabberImage.loadFromFile("png/menu/grabber.png");
    grabberHoverImage.loadFromFile("png/menu/grabber_hover.png");
    sliderTexture.loadFromImage(sliderImage);
    grabberTexture.loadFromImage(grabberImage);
    grabberHoverTexture.loadFromImage(grabberHoverImage);
    sliderSprite.setTexture(sliderTexture);
    sliderSprite.setOrigin(sf::Vector2f(0, 32));
    sliderSprite.setTextureRect(sf::IntRect(0, 0, 512, 64));
    sliderSprite.setPosition(sf::Vector2f(x, y));
    grabberSprite.setTexture(grabberTexture);
    grabberSprite.setOrigin(sf::Vector2f(24, 32));
    grabberSprite.setTextureRect(sf::IntRect(0, 0, 48, 64));
    grabberSprite.setPosition(sliderSprite.getPosition() + sf::Vector2f(512, 0));
    grabberHoverSprite.setTexture(grabberHoverTexture);
    grabberHoverSprite.setOrigin(sf::Vector2f(24, 32));
    grabberHoverSprite.setTextureRect(sf::IntRect(0, 0, 48, 64));
    grabberHoverSprite.setPosition(sliderSprite.getPosition() + sf::Vector2f(512, 0));

    grab = false;
}

bool Slider::Hover(sf::RenderWindow &window)
{
    if (!grab)
    {
        cursor_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if ( grabberSprite.getGlobalBounds().contains(cursor_pos) )
        {
            cursor.loadFromSystem(sf::Cursor::Hand);
            window.setMouseCursor(cursor);
            grabberHoverSprite.setColor(sf::Color(255, 255, 255, 100));
            return true;
        }
    }
    else
    {
        cursor.loadFromSystem(sf::Cursor::Hand);
        window.setMouseCursor(cursor);
        grabberHoverSprite.setColor(sf::Color(255, 255, 255, 100));
        return true;
    }

    grabberHoverSprite.setColor(sf::Color(255, 255, 255, 0));
    return false;
}

float Slider::Change(sf::RenderWindow &window, bool mousePressed, bool mouseReleased)
{
    cursor_pos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (mousePressed)
    {
        if ( (sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (grabberSprite.getGlobalBounds().contains(cursor_pos)) )
        {
            grab = true;
        }
    }
    else if (mouseReleased)
    {
        grab = false;
    }

    if (grab)
    {
        grabberSprite.setPosition(sf::Vector2f(cursor_pos.x, grabberSprite.getPosition().y));
        if (grabberSprite.getPosition().x < sliderSprite.getPosition().x)
        {
            grabberSprite.setPosition(sf::Vector2f(sliderSprite.getPosition().x, grabberSprite.getPosition().y));
        }
        else if (grabberSprite.getPosition().x > sliderSprite.getPosition().x + 512)
        {
            grabberSprite.setPosition(sf::Vector2f(sliderSprite.getPosition().x + 512, grabberSprite.getPosition().y));
        }
        grabberHoverSprite.setPosition(grabberSprite.getPosition());

        return grabberSprite.getPosition().x - sliderSprite.getPosition().x;
    }

    return -1;
}
