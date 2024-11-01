#ifndef LABEL_H
#define LABEL_H

#include <SFML/Graphics.hpp>

using namespace std;

class Label
{
public:
    Label(string text, float x, float y);

    void Draw(sf::RenderWindow &window, float cameraX);

    sf::Font font;
    sf::Text label;
};

#endif // LABEL_H
