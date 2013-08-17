#include "Player.h"


sf::Vector2f Player::getPosition() {
    return position;
}

Player::Player(void) {
    position = sf::Vector2f( 1.0f, 1.0f );
}


Player::~Player(void) {
}
