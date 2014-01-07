#pragma once
#include <SFML/Graphics.hpp>
#include <stack>
#include "GameState.h"

class GameWindow : public sf::RenderWindow {
public:
    ~GameWindow(void);

    static GameWindow *getGameWindow();

    // Constructs a square sprite of the specified color, with sides of the 
    // given size, and with a black outline.
    static sf::Sprite *makeSquareSprite( sf::Color color, int size );

    // Constructs a circular sprite of the specified colour.
    static sf::Sprite *makeCircleSprite( sf::Color );
    
    void mainLoop();

    // Adds a new GameState to the stack.
    void pushNewState( GameState *state );

private: 
    GameWindow( sf::VideoMode videoMode, std::string title );

    static GameWindow *singleton;

    sf::Font font;
    std::stack<GameState *> gameStates;

    void drawStateStack();
};

