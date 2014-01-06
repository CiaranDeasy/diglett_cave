#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "InventoryGUI.h"
#include "Item.h"
#include "NewItemVisual.h"
#include <vector>
#include "HullGUI.h"

class GameWindow : public sf::RenderWindow {
public:
    static GameWindow *getGameWindow();

    // Constructs a square sprite of the specified color, with sides of the 
    // given size, and with a black outline.
    static sf::Sprite *makeSquareSprite( sf::Color color, int size );

    static sf::Sprite *makeCircleSprite( sf::Color );

    void toggleInventoryGUI();
    
    void GameWindow::mainLoop();
    void handleWindowEvents();
    void drawWorld();
    void drawPlayer();
    void drawGUI();

    ~GameWindow(void);
    void toggleDebugOverlay();
    void triggerNewItemVisuals();

private: 

    static GameWindow *singleton;
    sf::Sprite *playerSprite;
    sf::Sprite *playerDeadSprite;
    sf::Sprite *debugOverlayBackground;
    sf::View worldView;
    sf::View interfaceView;
    sf::Font font;
    bool showDebugOverlay;
    InventoryGUI inventoryGUI;
    std::vector<NewItemVisual *> newItemVisuals;
    HullGUI hullGUI;
    int expectedInventorySize;

    void createSprites();
    sf::Sprite *makeDebugOverlayBackground();
    void drawDebugOverlay();
    GameWindow( sf::VideoMode videoMode, std::string title );
};

