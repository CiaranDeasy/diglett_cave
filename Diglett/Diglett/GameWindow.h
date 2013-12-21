#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class GameWindow {
public:
    static GameWindow *getGameWindow();
    void GameWindow::mainLoop();
    ~GameWindow(void);
    void toggleDebugOverlay();
private: 

    static GameWindow *singleton;
    sf::RenderWindow *window;
    // Index into this array using the enum Tile::TileType.
    sf::Sprite *tileSprites[ Tile::Count ];
    sf::Sprite *playerSprite;
    sf::Sprite *debugOverlayBackground;
    sf::View worldView;
    sf::View interfaceView;
    sf::Font debugFont;
    bool showDebugOverlay;

    void createSprites();
    sf::Sprite *makeSquareSprite( sf::Color );
    sf::Sprite *makeCircleSprite( sf::Color );
    sf::Sprite *makeDebugOverlayBackground();
    void drawDebugOverlay();
    GameWindow(void);
};

