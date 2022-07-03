#include "clouds.h"

clouds::clouds(): sf::RectangleShape({114,27})
{
    x=rand()%685;
    y=rand()%600;
    setPosition(x, y);
    texture.loadFromFile("cloud.png");
    setTexture(&texture);

}

void clouds::poruszanie(float speed, sf::Time &time)
{
    auto bounding_box= getGlobalBounds();
    if(bounding_box.left<=0)
    {
        speed=std::abs(speed);

    }
    if(bounding_box.left>=800)
    {
        setPosition(0,getPosition().y);

    }
    move(speed * time.asSeconds(), 0);

}

void clouds::bump(float predkosc){
    move(0,-predkosc);
}

float clouds::pozycja()
{
    float pozycja=getPosition().y;
    return pozycja;
}

void clouds::nowapozycja()
{
    setPosition(rand()%685,0);
}
