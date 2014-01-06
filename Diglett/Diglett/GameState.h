#pragma once
#include "InputHandler.h"
#include <SFML/Graphics.hpp>

/* This abstract class represents a state that the game can be in, such as the
   main game, or a particular menu. */

class GameState : public sf::Drawable {
public:
    GameState();
    ~GameState();

    // Represents the behaviour that should be performed each game tick when 
    // the game is in this state.
    virtual void gameTick() = 0;

    // Indicates whether the game state below this one should be drawn behind 
    // it, eg: if this is a menu overlaying the main game.
    virtual bool drawUnderlyingState() = 0;

private: 

};

