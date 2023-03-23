// Include necessary libraries
#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include <chrono>


// Define a class for the ball
class Ball
{
private:
    bool gameStarted = false; // Boolean to check if game has started or not
    const float pi = 3.14159265358979323846f; // Define the value of pi as a float constant
    sf::Vector2f velocity; // Velocity of the ball
    sf::Vector2f position; // Position of the ball
    float speed; // Speed of the ball
    float radius; // Radius of the ball
    sf::CircleShape ball; // Circle object for the ball

    sf::SoundBuffer collisionSoundBuffer;
    sf::Sound collisionSound;

    sf::SoundBuffer brickExplosion_SoundBuffer;
    sf::Sound brickExplossionSound;

    int points = 0;

public:

    // Constructor for the ball object
    Ball(sf::Vector2f ballPosition, float ballRadius, float ballSpeed, sf::RenderWindow& window)
    : velocity(0,0)
    , speed(ballSpeed)
    , position(ballPosition)
    , radius(ballRadius)
    {
        // Set the radius and origin of the ball circle shape
        ball.setRadius(ballRadius);
        ball.setOrigin(ballRadius,ballRadius);

        // Set the position of the ball
        ball.setPosition(ballPosition);
        if(!collisionSoundBuffer.loadFromFile("src/audio/playerBallCollisionSound.wav")){
            std::cout << "Couldn't load the explosion sound" << std::endl;
        }
        if(!brickExplosion_SoundBuffer.loadFromFile("src/audio/brickExplosion.wav")){
            std::cout << "Couldn't load the explosion sound" << std::endl;
        }
        collisionSound.setBuffer(collisionSoundBuffer);
        brickExplossionSound.setBuffer(brickExplosion_SoundBuffer);
    }


    // Function to process events (key presses) for the ball object
    void processEvents(sf::Keyboard::Key key, bool checkPressed)
    {
        // Check if key is pressed and game has not started
        if(checkPressed){
            
            if(!gameStarted){
                // Check if key pressed is space
                if(key == sf::Keyboard::Space){
                    // Generate random angle for the ball movement
                    std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
                    std::uniform_real_distribution<float> dist(-140.0f, -20.0f);
                    float angle = dist(rng) * pi / 180.0f;

                    // Calculate velocity of the ball based on the random angle and speed
                    velocity = sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);

                    // Set gameStarted to true
                    gameStarted = true;

                    // Print message to console indicating that game has started
                    std::cout << "Game started!" << std::endl;
                }
            }

        }
    }

    // Function to update the position of the ball
    void update(sf::RenderWindow& window, Player& player)
    {
        // Check if game has started
        
        if(gameStarted){
            // Update the position of the ball
            position += velocity;
            ball.setPosition(position);

            // Check if ball has hit the left or right wall and reverse velocity accordingly
            if(position.x - radius < 0){
                collisionSound.play();
                velocity.x = speed;
            }
            else if(position.x + radius > window.getSize().x){
                collisionSound.play();
                velocity.x = -speed;
            }

            // Check if ball has hit the top or bottom wall and reverse velocity accordingly
            if(position.y - radius < 0){
                collisionSound.play();
                velocity.y = speed;
            }
            if(position.y + radius > window.getSize().y){
                collisionSound.play();
                velocity.y = -speed;
            }
            if(collidesWithPlayer(player)){
                collisionSound.play();
                velocity.y = -velocity.y;
            }            

            
        }
    }
    
  
    bool collidesWithPlayer(Player& player){
        sf::FloatRect ballBounds = ball.getGlobalBounds();
        sf::FloatRect playerBounds;
        player.getBounds(playerBounds);
        if(ballBounds.intersects(playerBounds)){
        std::cout << playerBounds.left << std::endl;
        std::cout << playerBounds.top << std::endl;
        std::cout << playerBounds.height << std::endl;
        std::cout << playerBounds.width << std::endl;
        }
        return ballBounds.intersects(playerBounds);
        
    }

    void collidesWithBrick(Brick& brick, int& brickNum, std::vector<Brick>& brickVector){        sf::FloatRect ballBounds = ball.getGlobalBounds();
        sf::FloatRect brickBounds = brick.getBounds();
        if(ballBounds.intersects(brickBounds)){
            points++;
            brickExplossionSound.play();
            velocity.y = -velocity.y;
            brickVector.erase(brickVector.begin() + brickNum);
        }
    }
    int getPoints(){
        return points;
    }

    int yPosition(){
        return ball.getPosition().y;
    }

    void stop(){
        sf::Vector2f stop(0,0);
        velocity = stop;
    }

    // Function to draw the ball on the window
    void drawTo(sf::RenderWindow& window)
    {
        window.draw(ball);
    }
};
