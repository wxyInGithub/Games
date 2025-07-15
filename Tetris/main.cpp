#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>

const int M = 20;
const int N = 10;
int fields[M][N] = {0};

int features[7][4] = {
        1, 3, 5, 7,     //l
        2, 3, 4, 5,     //0
        3, 5, 7, 6,     //_|
        2, 3, 5, 7,     //L
        3, 5, 4, 7,     //T
        3, 5, 4, 6,     //Z
        2, 4, 5, 7,     //S
};

struct Point{
    int x, y;
} a[4], b[4];
void getPosition(int n);

int main() {
    sf::RenderWindow window(sf::VideoMode(320, 480), "Tetris");
    sf::Texture tiles;
    tiles.loadFromFile("../images/tiles.png");
    sf::Sprite brick(tiles);
    int color = rand() % 8;
    brick.setTextureRect(sf::IntRect(color*18, 0, 18, 18));
    int dx = 0;bool rotate = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if(event.type == sf::Event::KeyPressed)
                switch (event.key.code) {
                case sf::Keyboard::A: dx=-1;break;
                case sf::Keyboard::D: dx=1;break;
                case sf::Keyboard::Space: rotate=true;break;
                default: break;
                }
        }
        ////    Move    ////
        for(int i=0;i<4;++i)    a[i].x += dx;
        //////////   Rotate   //////////
        if(rotate)
        {
            Point p = a[1];
            for(int i=0;i<4;++i)
            {
                int dx = a[i].x - p.x;
                int dy = a[i].y - p.y;
                a[i].x = p.x - dy;
                a[i].y = p.y + dx;
            }
        }

        if(a[0].x == 0) getPosition(rand()%7);
        dx = 0;rotate = 0;

        window.clear(sf::Color::White);
        for(int i=0;i<4;++i)
        {
            brick.setPosition(a[i].x*18, a[i].y*18);
            window.draw(brick);
        }
        window.display();
    }

    return 0;
}


void getPosition(int n)
{
    for(int i=0;i<4;++i)
    {
        a[i].x = features[n][i] % 2;
        a[i].y = features[n][i] / 2;
    }
}
