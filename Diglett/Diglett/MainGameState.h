#pragma once
#include "GameState.h"
#include "InventoryGUI.h"
#include "NewItemVisual.h"
#include "HullGUI.h"
#include "GameWindow.h"
#include "DebugOverlayGUI.h"
#include "Tutorial/TutorialHandler.h"
#include "MoneyGUI.h"

/* This abstract class represents a state that the game can be in, such as the
   main game, or a particular menu. */

class MainGameState : public GameState {
public:
    MainGameState( sf::Font& font, GameWindow *gameWindow );
    ~MainGameState();
    
    static void setInterfaceView( sf::RenderTarget& target );
    static void setWorldView( sf::RenderTarget& target );

    // Represents the behaviour that should be performed each game tick when 
    // the game is in this state.
    virtual void gameTick();

    // Draws all elements of the game state.
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    // Indicates whether the game state below this one should be drawn behind 
    // it, eg: if this is a menu overlaying the main game.
    virtual bool drawUnderlyingState();
    
    void toggleDebugOverlay();
    void toggleInventoryGUI();
    void triggerNewItemVisuals();

    void openShop();

private: 
    class MainInputHandler : public InputHandler {
    public:
        MainInputHandler( MainGameState& gameState );
        ~MainInputHandler();

        // Check key and button status and events, and update the game state 
        // appropriately.
        void processInputs();
        Direction getDirectionOfMovement() { return directionOfMovement; }
    private:
        static const float PLAYER_SPEED;
        static const float DIAG_PLAYER_SPEED;
        Direction directionOfMovement;
        MainGameState& gameState;

        Direction classifyDirectionOfMovement(
            float stickPositionX, float stickPositionY);
    };
    
    static const float CAMERA_ZOOM;

    GameWindow *gameWindow;
    sf::Font& font;
    sf::Sprite *playerSprite;
    sf::Sprite *playerDeadSprite;
    InventoryGUI inventoryGUI;
    std::vector<NewItemVisual *> newItemVisuals;
    HullGUI hullGUI;
    DebugOverlayGUI debugOverlayGUI;
    MainInputHandler inputHandler;
    int expectedInventorySize;
    TutorialHandler tutorials;
    MoneyGUI moneyGUI;
    
    void createSprites();
    void handleWindowEvents();
    void drawWorld( sf::RenderTarget& target ) const;
    void drawPlayer( sf::RenderTarget& target ) const;
    void drawGUI( sf::RenderTarget& target ) const;

    // Ages the NewItemVisuals by one tick, and deletes any that die.
    void processNewItemVisuals();

};