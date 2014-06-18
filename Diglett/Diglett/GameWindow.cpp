#include "GameWindow.h"
#include "Constants.h"
#include "Tile.h"
#include "Item.h"
#include "MenuGameState.h"
#include "Resources.h"

GameWindow::~GameWindow(void) {
}

GameWindow *GameWindow::singleton = NULL;

GameWindow *GameWindow::getGameWindow() {
    if( singleton == NULL ) {
        singleton = new GameWindow( 
            sf::VideoMode( WINDOW_RESOLUTION.x, WINDOW_RESOLUTION.y ), 
            WINDOW_TITLE );
    }
    return singleton;
}

void GameWindow::mainLoop() {
    while( this->isOpen() ) {
		float deltaTime = ( (float) clock.getElapsedTime().asMicroseconds() ) / 1000.f;
		clock.restart();
        // Cleanup dead game states.
        while( gameStates.top()->isDead() ) {
            delete gameStates.top();
            gameStates.pop();
        }
        gameStates.top()->gameTick( deltaTime );
        drawStateStack();
        this->display();
    }
}

void GameWindow::pushNewState( GameState *state ) {
    gameStates.push( state );
}

GameWindow::GameWindow( sf::VideoMode videoMode, std::string title ) :
            sf::RenderWindow( videoMode, title ),
            gameStates(),
            clock() {
	this->setFramerateLimit(60);

    Tile::initialiseTypes();
    Item::initialiseTypes();

    gameStates.push( new MenuGameState( this ) );
}

const std::string GameWindow::WINDOW_TITLE = "Diglett";

void GameWindow::drawStateStack() {
    GameState *topState = gameStates.top();
    if( topState->drawUnderlyingState() ) {
        gameStates.pop();
        drawStateStack();
        gameStates.push( topState );
    }
    draw( *topState );
}
