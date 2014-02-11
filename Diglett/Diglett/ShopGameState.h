#pragma once
#include "GameState.h"
#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include "ShopGUI.h"
#include "Player.h"

/* This class represents the game state where the main game is suspended and a 
   text pop-up is displayed until the player dismisses it. */

class ShopGameState : public GameState {
public:
    ShopGameState( 
            GameWindow *gameWindow, sf::Font& font, Player& player );
    ~ShopGameState();

    class ShopInputHandler : public InputHandler {
    public:
        ShopInputHandler( ShopGameState& gameState );
        ~ShopInputHandler();

        void processInputs();

    private:
        ShopGameState& gameState;
    };

    friend class ShopInputHandler;

    // Represents the behaviour that should be performed each game tick when 
    // the game is in this state.
    virtual void gameTick();

    // Draws all elements of the game state.
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Indicates whether the game state below this one should be drawn behind 
    // it, eg: if this is a menu overlaying the main game.
    virtual bool drawUnderlyingState();

    // Sells all items in the player's inventory.
    void sell();

private: 
    ShopInputHandler inputHandler;
    GameWindow *gameWindow;
    sf::Font font;
    ShopGUI shopGUI;
    Player& player;

    // Polls the GameWindow for window events and responds to them accordingly.
    void handleWindowEvents();
};

