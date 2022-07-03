#pragma once
#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class background : public sf::Sprite
{
public:
    background();;

private:
    sf::Texture texture;
};

#endif // BACKGROUND_H
