#pragma once
#ifndef INPUT_HANDLER_H
#define INPUT_HANDLER_H

#include <SFML/Window.hpp>
#include <vector>

class InputHandler {
public:
    InputHandler();
    ~InputHandler();

    // Check key and button status and events, and update the game state 
    // appropriately.
    virtual void processInputs() = 0;
    
    // Adds a button event to the list of input events to handle on the next 
    // call to processInputs().
    void addEvent( sf::Event );
    
    // A list of button events since the last processInputs().
    std::vector<sf::Event> buttonsPressed;

protected:
    // Minimum displacement required on analogue stick axis to accept as movement.
    // Value 0-100.
    static const float CONTROLLER_DEADZONE;

};

#endif // INPUT_HANDLER_H