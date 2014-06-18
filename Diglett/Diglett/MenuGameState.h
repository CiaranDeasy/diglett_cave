#pragma once
#ifndef MENU_GAME_STATE_H
#define MENU_GAME_STATE_H

#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include "TextPopUp.h"
#include "Player.h"

/* This abstract class represents a state that the game can be in, such as the
   main game, or a particular menu. */

class MenuGameState : public GameState {
public:
    MenuGameState( GameWindow *gameWindow );
    ~MenuGameState();

    // Represents the behaviour that should be performed each game tick when 
    // the game is in this state.
    virtual void gameTick( float deltaTime );

    // Draws all elements of the game state.
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Indicates whether the game state below this one should be drawn behind 
    // it, eg: if this is a menu overlaying the main game.
    virtual bool drawUnderlyingState();

private: 
    class MenuInputHandler : public InputHandler {
    public:
        MenuInputHandler( MenuGameState& gameState );
        ~MenuInputHandler();
        void processInputs();

    private:
        MenuGameState& gameState;
    };
    friend class MenuInputHandler;
	
	static const std::string SPRITE_FILE;

    MenuInputHandler inputHandler;
    GameWindow *gameWindow;
    Player& player;
	sf::Texture* logoTexture;
	sf::Sprite* logoSprite;
	sf::Text* text;

    // Polls the GameWindow for window events and responds to them accordingly.
    void handleWindowEvents();

	// Pushes the MainGameState to start the game.
	void launchGame();
};

#endif // MENU_GAME_STATE_H
