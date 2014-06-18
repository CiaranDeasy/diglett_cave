#pragma once
#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include <stack>
#include "GameState.h"

class GameWindow : public sf::RenderWindow {
public:
    ~GameWindow(void);

    static GameWindow *getGameWindow();
    
    // The top-level main loop of the program.
    void mainLoop();

    // Adds a new GameState to the stack.
    void pushNewState( GameState *state );

private: 
    GameWindow( sf::VideoMode videoMode, std::string title );

    static GameWindow *singleton;
    static const std::string WINDOW_TITLE;
	sf::Clock clock;

    std::stack<GameState *> gameStates;

    void drawStateStack();
};

#endif // GAMEWINDOW_H
