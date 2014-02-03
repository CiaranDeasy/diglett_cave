#include "Gamestate.h"

GameState::GameState() {
    dead = false;
}

GameState::~GameState() {
}

bool GameState::isDead() { return dead; }

void GameState::setInterfaceView( sf::RenderTarget& target ) {
    sf::View interfaceView = sf::View( sf::FloatRect( 
            0, 0, target.getSize().x, target.getSize().y ) );
    target.setView( interfaceView );
}