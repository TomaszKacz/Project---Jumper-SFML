#include "champ.h"

champ::champ(): sf::RectangleShape({97,120})
{
    setPosition(400, 300);
    texture.loadFromFile("champ.png");
    setOrigin(48.5,60);
    setScale(1,1);
    setTexture(&texture);
}

bool champ::colision(clouds &clouds,int score)
{
    auto bounding_box=getGlobalBounds();
    if(bounding_box.intersects(clouds.getGlobalBounds())&&speedy>00&&score!=100)
    {
        speedy=-15;
        return true;
    }
    return false;

}

int champ::movement(const sf::Time &time, bool gameover)
{
    auto bounding_box=getGlobalBounds();
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)&&gameover!=true)
    {
        if(bounding_box.left<=0)
        {

        }
        else
        {
            move(-500 * time.asSeconds(),0);
            setScale(-1,1);
        }

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)&&gameover!=true)
    {
        if(bounding_box.left+bounding_box.width>=800)
        {

        }
        else
        {
            move(500 * time.asSeconds(), 0);
            setScale(1,1);
        }


    }
    if(bounding_box.top+bounding_box.height>=600)
    {
        return -1;
    }
    move(0,speedy);
    speedy=speedy+0.2;
    return 1;
}

float champ::gety()
{
    return getPosition().y;
}

void champ::sety(int y)
{
    setPosition(getPosition().x,y);
}

float champ::getspeed()
{
    return speedy;
}
