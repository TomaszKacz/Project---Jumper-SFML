
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include <sstream>
#include <iostream>
#include<time.h>
class background : public sf::Sprite
{
public:
    background(): sf::Sprite()
    {
        texture.loadFromFile("background.png");
        setTexture(texture);
    }
private:
    sf::Texture texture;
};

class clouds : public sf::RectangleShape
{
public:

    clouds(): sf::RectangleShape({114,27})
    {
        x=rand()%685;
        y=rand()%600;
        setPosition(x, y);
        texture.loadFromFile("cloud.png");
        setTexture(&texture);
    }
    void poruszanie(float speed, sf::Time &time)
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

    void bump(float predkosc){
        move(0,-predkosc);
    }
    float pozycja()
    {
        float pozycja=getPosition().y;
        return pozycja;
    }
    void nowapozycja()
    {
        setPosition(rand()%685,0);
    }
    int x,y;
private:
    sf::Texture texture;
};

class champ : public sf::RectangleShape
{
public:
    champ(): sf::RectangleShape({97,120})
    {
        setPosition(400, 300);
        texture.loadFromFile("champ.png");
        setOrigin(48.5,60);
        setScale(1,1);
        setTexture(&texture);
    }

    bool colision(clouds &clouds,int score)
    {
        auto bounding_box=getGlobalBounds();
        if(bounding_box.intersects(clouds.getGlobalBounds())&&speedy>0&&score!=100)
        {
            speedy=-15;
            return true;
        }
        return false;
    }
    int movement(const sf::Time &time, bool gameover)
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
    float gety()
    {
        return getPosition().y;
    }

    void sety(int y)
    {
        setPosition(getPosition().x,y);
    }
    float getspeed()
    {
        return speedy;
    }
private:
    float speedy=0;
    //tekstura
    sf::Texture texture;
};

int main()
{

    bool gameoverbool=false,wygrana=false;
    int score=0;
    sf::Font arial;
    arial.loadFromFile("arial.ttf");
    std::ostringstream striScore,gameover,kont,juwin;
    striScore << "Score: " << score;
    gameover << "Game Over! ";
    kont<<"Press return to exit! ";
    juwin << "You Win! ";
    sf::Text Score,end,kontinue,uwin;
    Score.setCharacterSize(30);
    Score.setPosition({ 10, 10 });
    Score.setFont(arial);
    Score.setString(striScore.str());

    end.setCharacterSize(100);
    end.setPosition({ 150, 225 });
    end.setFont(arial);
    end.setString(gameover.str());

    kontinue.setCharacterSize(30);
    kontinue.setPosition({250,360});
    kontinue.setFont(arial);
    kontinue.setString(kont.str());

    uwin.setCharacterSize(100);
    uwin.setPosition({ 150, 225 });
    uwin.setFont(arial);
    uwin.setString(juwin.str());

    clouds clouds[10];
    background background;

    champ champ;

    sf::RenderWindow window(sf::VideoMode(800, 600), "Pawel Jumper");
    window.setVerticalSyncEnabled(true);
    sf::Clock clock;
    sf::Music main;
    if(!main.openFromFile("theme.ogg"))
    {
        std::cout<<"blad wczywytania muzyki - theme"<<std::endl;
    }
    main.setVolume(5);
    main.play();
    sf::SoundBuffer soundbf,sb2,sb3,sb4;
    sf::Sound skok,combo,koniec,win;
    if(!soundbf.loadFromFile("jump.wav"))
        {
             std::cout<<"blad wczytywania muzyki - jump"<<std::endl;
        }
    skok.setBuffer(soundbf);
    skok.setVolume(15);
    if(!sb2.loadFromFile("combo.wav"))
        {
             std::cout<<"blad wczytywania muzyki - combo"<<std::endl;
        }
    combo.setBuffer(sb2);
    combo.setVolume(15);
    if(!sb3.loadFromFile("dies.wav"))
    {
         std::cout<<"blad wczytywania muzyki - koniec"<<std::endl;
    }
    koniec.setBuffer(sb3);
    koniec.setVolume(15);

    if(!sb4.loadFromFile("win.wav"))
        {
             std::cout<<"blad wczytywania muzyki - win"<<std::endl;
        }

    win.setBuffer(sb4);
    win.setVolume(15);

    while (window.isOpen())
    {

        sf::Time elapsed = clock.restart();
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }


        window.draw(background);
        window.draw(champ);
        window.draw(Score);

        champ.movement(elapsed,gameoverbool);

        if(champ.movement(elapsed,gameoverbool)==-1&&wygrana!=true)
        {
            if(gameoverbool==false)
            {
            koniec.play();
            window.draw(end);
            window.draw(kontinue);
            main.stop();
            gameoverbool=true;
            };

            if(gameoverbool==true)
            {
                window.draw(end);
                window.draw(kontinue);
                if(event.key.code==sf::Keyboard::Return)
                    return 0;
            }


        }

        for(int i=0;i<10;i++)
        {
            if(champ.colision(clouds[i],score)==true&&!(score>=100))
            {

                if(((score)!=100))
                {
                    score++;
                    skok.play();
                }
                striScore.str("");
                striScore << "Score " << score;
                Score.setString(striScore.str());
            }
        }

        if((score+1)%10==0&&(score+1)!=100)
        {
            combo.play();
        }

        if (champ.gety()< 200)
        {

            for (int i = 0; i < 10; ++i)
            {
                champ.sety(200);
                clouds[i].bump(champ.getspeed());
                if(clouds[i].pozycja()>600)
                {
                    clouds[i].nowapozycja();
                }
            }
        }

        if(score>40&&score<=70&&gameoverbool!=true)
        {
            for(int i=0;i<10;i++)
            {
                clouds[i].poruszanie(300,elapsed);
            }
        }

        if(score>70&&gameoverbool!=true)
        {
            for(int i=0;i<10;i++)
            {
                clouds[i].poruszanie(500,elapsed);
            }
        }

        if(score>=100)
        {
            if(gameoverbool==false)
            {
            win.play();
            window.draw(uwin);
            window.draw(kontinue);
            main.stop();
            gameoverbool=true;
            wygrana=true;
            };

            if(gameoverbool==true)
            {
                window.draw(uwin);
                window.draw(kontinue);
                if(event.key.code==sf::Keyboard::Return)
                    return 0;
            }
        }

        for(int i=0;i<10;i++)
        {
            window.draw(clouds[i]);
        }

        window.display();
    }

    return 0;
}
