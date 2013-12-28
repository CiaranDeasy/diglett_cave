#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "InventoryGUI.h"

class GameWindow {
public:
    static GameWindow *getGameWindow();

    // Constructs a square sprite of the specified color, with sides of the 
    // given size, and with a black outline.
    static sf::Sprite *makeSquareSprite( sf::Color color, int size );

    static sf::Sprite *makeCircleSprite( sf::Color );

    void toggleInventoryGUI();
    
    void GameWindow::mainLoop();
    ~GameWindow(void);
    void toggleDebugOverlay();
private: 

    static GameWindow *singleton;
    sf::RenderWindow *window;
    sf::Sprite *playerSprite;
    sf::Sprite *debugOverlayBackground;
    sf::View worldView;
    sf::View interfaceView;
    sf::Font font;
    bool showDebugOverlay;
    InventoryGUI inventoryGUI;

    void createSprites();
    sf::Sprite *makeDebugOverlayBackground();
    void drawDebugOverlay();
    GameWindow(void);
};

