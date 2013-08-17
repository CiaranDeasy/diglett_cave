#include "Player.h"


sf::Vector2f Player::getPosition() {
    return position;
}

void Player::move( float x, float y ) {
    position = sf::Vector2f( position.x + x, position.y + y );
}

Player::Player(void) {
    position = sf::Vector2f( 1.0f, 1.0f );
}


Player::~Player(void) {
}
