#include "Player.h"
#include <iostream>

Player& Player::getPlayer() {
    return singleton;
}

sf::Vector2f Player::getPosition() {
    return position;
}

void Player::move( float x, float y ) {
    // The program will crash if attempting to load a chunk outside the world.
    // Constrain movement until infinite worlds are implemented.
    if( position.x + x > 150 || position.x + x < -150 
        || position.y + y > 150 || position.y + y < -150 ) 
        return;
    position = sf::Vector2f( position.x + x, position.y + y );
}

Player Player::singleton = Player();

Player::Player(void) {
    position = sf::Vector2f( 1.0f, 1.0f );
}


Player::~Player(void) {
}
