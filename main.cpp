#include <SFML/Graphics.hpp>
#include "src/entities/Player.hpp"
#include "src/entities/Brick.hpp"
#include "src/entities/Ball.hpp"
int main()
{
    constexpr int fps = 50;
    constexpr bool vsync = false; 
    // Create the window with a size of 1200x800 pixels
    sf::RenderWindow window(sf::VideoMode(1200, 800), "Arkanoid - Created by Raven");
    window.setFramerateLimit(fps);
    window.setVerticalSyncEnabled(vsync);        
    // Create the player object and set its position
    Player plr(window.getSize().x / 10, window.getSize().y / 42);
    plr.setPosition(window);

    sf::Font font;
    if(!font.loadFromFile("src/font.TTF"))
    {
        std::cout << "Couldn't load the font" << std::endl;
    }

    struct Texts
    {
        sf::Text win;
        sf::Text loss;
    } text;
    
    text.win.setFont(font);
    text.loss.setFont(font);

    text.win.setString("You   won!");
    text.loss.setString("You   lost o7");

    text.win.setCharacterSize(60);
    text.loss.setCharacterSize(60);

    text.win.setFillColor(sf::Color::White);
    text.loss.setFillColor(sf::Color::White);

    text.win.setPosition(window.getSize().x / 3, window.getSize().y / 2);
    text.loss.setPosition(window.getSize().x / 3, window.getSize().y / 2);

    // Create the ball object and set its position
    const float ballRadius = 13.f;
    sf::Vector2f ballPosition;
    ballPosition.x = window.getSize().x / 2;
    ballPosition.y = window.getSize().y / 1.23;
    const float ballSpeed = 6.0f;
    Ball ball(ballPosition, ballRadius, ballSpeed, window);

    // Create the bricks
    int columns = 4;
    int rows = 12;
    
    //Todo: The col var is unnecessary, fix it
    sf::Vector2f defaultPosition(0,0);
    std::vector<Brick> brickGrid;
    for(int col = 0; col < columns; col++) {
        for(int row = 0; row < rows; row++){
            Brick newBrick(defaultPosition, window);
            brickGrid.push_back(newBrick);
            defaultPosition.x += 100;
        }
        defaultPosition.x = 0;
        defaultPosition.y += 30;

    }
    
    // Main game loop
    while (window.isOpen()) 
    {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::KeyPressed)
                plr.processEvents(event.key.code, true);
                ball.processEvents(event.key.code, true);           
            if(event.type == sf::Event::KeyReleased)
                plr.processEvents(event.key.code, false);

            // Quit the game with the Q key
            if(event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Q)
                return 0;
        }

        // Clear the window
        window.clear();       


        // Draw the bricks
        for(int i = 0; i < columns*rows; i++){
            ball.collidesWithBrick(brickGrid[i], i, brickGrid);
            brickGrid[i].drawBrick();
        }
        // Update and draw the player
        plr.update(window);
        plr.drawTo(window);
        // Update and draw the ball
        ball.update(window, plr);   
        ball.drawTo(window);

        if(ball.yPosition() > window.getSize().y / 1.04){
            ball.stop();
            plr.stop();
            window.draw(text.loss);
        }
        if(ball.getPoints() == columns*rows){
            ball.stop();
            plr.stop();
            window.draw(text.win);
        }        

        // Display the window
        window.display();
    }

    return 0;
}
