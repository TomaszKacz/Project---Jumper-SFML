#pragma once
#ifndef CHAMP_H
#define CHAMP_H
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<clouds.h>

class champ : public sf::RectangleShape
{
public:
    champ();;
    bool colision(clouds &clouds,int score);;
    int movement(const sf::Time &time,bool gameover);;
    float gety();;
    void sety(int y);;
    float getspeed();;

private:
    float speedy=0;
    sf::Texture texture;
};

#endif // CHAMP_H
