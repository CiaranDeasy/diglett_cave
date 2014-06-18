#pragma once
#ifndef POP_UP_GAME_STATE_H
#define POP_UP_GAME_STATE_H

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include "TextPopUp.h"
#include "DismissInputHandler.h"

/* This class represents the game state where the main game is suspended and a 
   text pop-up is displayed until the player dismisses it. */

class PopUpGameState : public GameState {
public:
    PopUpGameState( GameWindow *gameWindow, std::string message );
    ~PopUpGameState();

    // Represents the behaviour that should be performed each game tick when 
    // the game is in this state.
    virtual void gameTick( float deltaTime );

    // Draws all elements of the game state.
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Indicates whether the game state below this one should be drawn behind 
    // it, eg: if this is a menu overlaying the main game.
    virtual bool drawUnderlyingState();

private: 
    DismissInputHandler inputHandler;
    GameWindow *gameWindow;
    TextPopUp popUp;

    // Polls the GameWindow for window events and responds to them accordingly.
    void handleWindowEvents();
};

#endif // POP_UP_GAME_STATE
