#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class GameWindow {
public:
    static GameWindow *getGameWindow();

    // Constructs a square sprite of the specified color, with sides of the 
    // given size, and with a black outline.
    static sf::Sprite *makeSquareSprite( sf::Color color, int size );

    static sf::Sprite *makeCircleSprite( sf::Color );

    void triggerInventoryGUI();

    void drawInventoryGUI();

    void clearInventoryGUI();

    void toggleInventoryGUI();

    static sf::Sprite *makeInventoryBackground( int x, int y );
    
    void GameWindow::mainLoop();
    ~GameWindow(void);
    void toggleDebugOverlay();
private: 

    static GameWindow *singleton;
    sf::RenderWindow *window;
    sf::Sprite *playerSprite;
    sf::Sprite *debugOverlayBackground;
    sf::Sprite *inventoryBackground;
    sf::View worldView;
    sf::View interfaceView;
    sf::Font debugFont;
    bool showDebugOverlay;
    static bool inventoryVisible;
    int expectedInventorySize;

    void createSprites();
    sf::Sprite *makeDebugOverlayBackground();
    void drawDebugOverlay();
    GameWindow(void);
};

