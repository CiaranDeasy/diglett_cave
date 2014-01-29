#pragma once
#include <SFML/Window.hpp>
#include <vector>
#include "InputHandler.h"
#include "GameState.h"

/* An input handler which removes the top GameState from the stack when 
   the appropriate input is received. */

class DismissInputHandler : public InputHandler {
public:
    DismissInputHandler( GameState& gamestate);
    ~DismissInputHandler();

    // Check key and button status and events, and update the game state 
    // appropriately.
    virtual void processInputs();

protected:
    GameState& gameState;

};

