#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


class Brick
{
    
private:
    sf::RectangleShape brick;
    sf::RenderWindow* win;

    sf::Vector2f brickParams;
    sf::Vector2f position;

    float padding = 7.f;
    int rows = 15;
    int columns = 4;
public:
    Brick(sf::Vector2f brickPos,sf::RenderWindow& window)
    {

        win = &window;
        
        brickParams.x = window.getSize().x / 14;
        brickParams.y = window.getSize().y / 42;

        brick.setSize(brickParams);

        position.x = brickPos.x + padding;
        position.y = brickPos.y + padding;

        brick.setPosition(position);    
        
    }

    sf::FloatRect getBounds(){
        return brick.getGlobalBounds();
    }
    
    void drawBrick(){
        win->draw(brick);
    }




};


/*
    // Create an array to hold the bricks
    Brick brick[b_columns][b_rows];

    
    //Center bricks
    float totalWidth = b_rows * (brickParams.x + padding) - padding;
    float startX = (window.getSize().x - totalWidth) / 2;

*/