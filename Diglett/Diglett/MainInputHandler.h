#pragma once
#ifndef MAIN_INPUT_HANDLER_H
#define MAIN_INPUT_HANDLER_H

#include <SFML/Window.hpp>
#include "InputHandler.h"
#include "MainGameState.h"

class MainInputHandler : InputHandler {
public:
    MainInputHandler( MainGameState& gameState );
    ~MainInputHandler();

    // Check key and button status and events, and update the game state 
    // appropriately.
    void processInputs();
    
    // Adds a button event to the list of input events to handle on the next 
    // call to processInputs().
    void addEvent( sf::Event );

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
    Direction getDirectionOfMovement() { return directionOfMovement; }
private:
    Direction directionOfMovement;
    MainGameState& gameState;

    Direction classifyDirectionOfMovement(
        float stickPositionX, float stickPositionY);
};

#endif // MAIN_INPUT_HANDLER_H
