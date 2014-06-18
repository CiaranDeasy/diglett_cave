#include "Gamestate.h"

GameState::GameState() {
    dead = false;
}

GameState::~GameState() {
}

bool GameState::isDead() { return dead; }

void GameState::setInterfaceView( sf::RenderTarget& target ) {
    sf::View interfaceView = sf::View( sf::FloatRect( 0.0f, 0.0f, 
		    (float) target.getSize().x, (float) target.getSize().y ) );
    target.setView( interfaceView );
}