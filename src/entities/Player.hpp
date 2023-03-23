#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Player
{
private:
    sf::RectangleShape player;
    sf::SoundBuffer collisionSoundBuffer;
    sf::Sound collisionSound;
    bool rightKeyPressed;
    bool leftKeyPressed;

    const float speed = 4.0f;
    float currentSpeed = speed;

    bool isAlive = true;
public:

    Player(float x, float y){
        if(!collisionSoundBuffer.loadFromFile("src/audio/collisionSound.wav")){
            std::cout << "Couldn't load the sound" << std::endl;
        }
        collisionSound.setBuffer(collisionSoundBuffer);
        player.setSize(sf::Vector2f(x,y));
        rightKeyPressed = false;
        leftKeyPressed = false;
        std::cout << "Player has been successfully created!" << std::endl;
    }
    ~Player(){
        std::cout << "Player has been deleted" << std::endl;
    }

    void processEvents(sf::Keyboard::Key key, bool checkPressed){

        if(checkPressed == true){
                if(key == sf::Keyboard::A){
                    leftKeyPressed = true;
                }
                if(key == sf::Keyboard::D){
                    rightKeyPressed = true;
                }
            }
        if(checkPressed == false){
            rightKeyPressed = false;
            leftKeyPressed = false;
        }

    }

    void update(sf::RenderWindow &window){
        if(isAlive){

            sf::Vector2f movement;

            //Movement
            if(leftKeyPressed){
            currentSpeed = -speed;
            }
            if(rightKeyPressed){
                currentSpeed = speed;
            }
            if(edgeColission(window) == -1){
                currentSpeed = speed;
            }else if(edgeColission(window) == 1){
                currentSpeed = -speed;
                
            }
            //Collision
            
            movement.x += currentSpeed;            
            player.move(movement);
        }
    }

    int edgeColission(sf::RenderWindow &window){
        if(player.getPosition().x < 0.0f){
            collisionSound.play();
            return -1;
        }else if((player.getPosition().x + player.getSize().x) > window.getSize().x){
            collisionSound.play();
            return 1;
        }else{
            return 0;
        }
        
    }

    void drawTo(sf::RenderWindow &window){
        window.draw(player);
    }

    void setPosition(sf::RenderWindow &window){

        player.setPosition(window.getSize().x / 2.f - player.getSize().x / 2.f, window.getSize().y - player.getSize().y - 22.f);

    }

    void stop(){
        isAlive = false;
    }

    void getBounds(sf::FloatRect &playerBounds){
        playerBounds = player.getGlobalBounds();
    }

};
