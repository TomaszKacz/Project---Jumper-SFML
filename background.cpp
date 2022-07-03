#include "background.h"

background::background(): sf::Sprite()
{
    texture.loadFromFile("background.png");
    setTexture(texture);
}
