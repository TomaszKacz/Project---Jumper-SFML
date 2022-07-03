
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include <sstream>
#include <iostream>
#include<time.h>
#include<background.h>
#include<clouds.h>
#include<champ.h>

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
        uwin.setPosition({ 200, 225 });
        uwin.setFont(arial);
        uwin.setString(juwin.str());
    clouds clouds[10];
    background background;
    champ champ;

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Jumper");
    window.setVerticalSyncEnabled(true);
    // run the program as long as the window is open
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
             std::cout<<"blad wczytywania muzyki - jump"<<std::endl;
        }
    win.setBuffer(sb4);
    win.setVolume(15);
    while (window.isOpen())
    {

        sf::Time elapsed = clock.restart();
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // clear the window with black color


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

                if(!(score>=100))
                {
                    score++;
                    skok.play();
                }
                striScore.str("");
                striScore << "Score " << score;
                Score.setString(striScore.str());
            }
        }

        if((score+1)%10==0&&!((score+1)>=100))
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
        // end the current frame
        window.display();
    }

    return 0;
}
