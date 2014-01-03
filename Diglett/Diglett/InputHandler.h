#pragma once
#include <SFML/Window.hpp>

class InputHandler {
public:
    // Check key and button status and events, and update the game state 
    // appropriately.
    static sf::Vector2f processInputs();
    
    // Adds a button event to the list of input events to handle on the next 
    // call to processInputs().
    static void addEvent( sf::Event );
    enum Direction {
        North = 0,
        Northnortheast = 1,
        Northeast = 2,
        Eastnortheast = 3,
        East = 4,
        Eastsoutheast = 5,
        Southeast = 6,
        Southsoutheast = 7,
        South = 8,
        Southsouthwest = 9,
        Southwest = 10,
        Westsouthwest= 11,
        West = 12,
        Westnorthwest = 13,
        Northwest = 14,
        Northnorthwest = 15,
        Null = 16
    };
    static Direction getDirectionOfMovement() { return directionOfMovement; }
private:
    // A list of button events since the last processInputs().
    static std::vector<sf::Event> buttonsPressed;
    static Direction directionOfMovement;
    static Direction classifyDirectionOfMovement(
        float stickPositionX, float stickPositionY);
};

