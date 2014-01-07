#include "GameWindow.h"
#include "Utility.h"
#include "Constants.h"
#include "Player.h"
#include "Physics.h"
#include "WorldData.h"
#include <SFML/Graphics.hpp>
#include "InputHandler.h"

void GameWindow::mainLoop() {
    while( this->isOpen() ) {
        // Cleanup dead game states.
        while( gameStates.top()->isDead() ) {
            gameStates.pop();
        }
        gameStates.top()->gameTick();
        drawStateStack();
        this->display();
    }
}

