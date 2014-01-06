#pragma once
#include <SFML/Window.hpp>
#include "Direction.h"

class InputHandler {
public:
    // Check key and button status and events, and update the game state 
    // appropriately.
    static sf::Vector2f processInputs();
    
    // Adds a button event to the list of input events to handle on the next 
    // call to processInputs().
    static void addEvent( sf::Event );
    static Direction getDirectionOfMovement() { return directionOfMovement; }
private:
    // A list of button events since the last processInputs().
    static std::vector<sf::Event> buttonsPressed;
    static Direction directionOfMovement;
    static Direction classifyDirectionOfMovement(
        float stickPositionX, float stickPositionY);
};

