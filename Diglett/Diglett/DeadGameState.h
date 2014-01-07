#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "GameWindow.h"

/* This abstract class represents a state that the game can be in, such as the
   main game, or a particular menu. */

class DeadGameState : public GameState {
public:
    DeadGameState( GameWindow *gameWindow );
    ~DeadGameState();

    // Represents the behaviour that should be performed each game tick when 
    // the game is in this state.
    virtual void gameTick();

    // Draws all elements of the game state.
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Indicates whether the game state below this one should be drawn behind 
    // it, eg: if this is a menu overlaying the main game.
    virtual bool drawUnderlyingState();

private: 

    class DeadInputHandler : public InputHandler {
    public:
        DeadInputHandler( DeadGameState& gameState );
        ~DeadInputHandler();
        void processInputs();

    private:
        DeadGameState& gameState;
    };
    friend class DeadInputHandler;

    DeadInputHandler inputHandler;
    GameWindow *gameWindow;

    // Polls the GameWindow for window events and responds to them accordingly.
    void handleWindowEvents();

    // Respawns the player, then marks the DeadGameState as dead.
    void respawn();
};

