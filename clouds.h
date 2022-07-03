#pragma once
#ifndef CLOUDS_H
#define CLOUDS_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<time.h>

class clouds : public sf::RectangleShape
{
public:
    clouds();;
    void poruszanie(float speed,sf::Time &time);;
    void bump(float predkosc);;
    float pozycja();;
    void nowapozycja();;
    int x,y;
private:
    sf::Texture texture;
};


#endif // CLOUDS_H
