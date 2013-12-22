#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"

class GameWindow {
public:
    static GameWindow *getGameWindow();
    static sf::Sprite *makeSquareSprite( sf::Color );
    static sf::Sprite *makeCircleSprite( sf::Color );
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
    sf::Font debugFont;
    bool showDebugOverlay;

    void createSprites();
    sf::Sprite *makeDebugOverlayBackground();
    void drawDebugOverlay();
    GameWindow(void);
};

