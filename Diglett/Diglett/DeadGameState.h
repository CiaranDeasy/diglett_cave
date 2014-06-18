#pragma once
#ifndef DEAD_GAME_STATE_H
#define DEAD_GAME_STATE_H

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include "TextPopUp.h"
#include "Player.h"

/* This abstract class represents a state that the game can be in, such as the
   main game, or a particular menu. */

class DeadGameState : public GameState {
public:
    DeadGameState( GameWindow *gameWindow, Player& player );
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

    // The message displayed, telling the player they are dead.
    static const std::string DEATH_MESSAGE;

    DeadInputHandler inputHandler;
    GameWindow *gameWindow;
    TextPopUp deadNotification;
    Player& player;

    // Polls the GameWindow for window events and responds to them accordingly.
    void handleWindowEvents();

    // Respawns the player, then marks the DeadGameState as dead.
    void respawn();
};

#endif // DEAD_GAME_STATE_H
