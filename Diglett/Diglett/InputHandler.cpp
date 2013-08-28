#include "InputHandler.h"
#include "Constants.h"
#include <SFML/Window.hpp>
#include "Player.h"

void InputHandler::processInputs() {
    bool skipKeyboard = false;

    // Controller
    float stickPositionX = 
        sf::Joystick::getAxisPosition( 0, sf::Joystick::X );
    float stickPositionY = 
        sf::Joystick::getAxisPosition( 0, sf::Joystick::Y );
    // If the stick is outside the deadzone, move the player.
    if( stickPositionX > CONTROLLER_DEADZONE || 
        stickPositionX < -CONTROLLER_DEADZONE || 
        stickPositionY > CONTROLLER_DEADZONE ||
        stickPositionY < -CONTROLLER_DEADZONE ) {
	    Player::getPlayer().move( 
            ( stickPositionX / 100 ) * PLAYER_SPEED, 
            ( stickPositionY / 100 ) * -PLAYER_SPEED );
        // Don't take keyboard input too.
        skipKeyboard = true;
    }

    // Keyboard
    if( !skipKeyboard ) {
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) {
			Player::getPlayer().move( 0, PLAYER_SPEED );
        }
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) {
			Player::getPlayer().move( 0, -PLAYER_SPEED );
        }
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ) {
			Player::getPlayer().move( -PLAYER_SPEED, 0 );
        }
		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) {
			Player::getPlayer().move( PLAYER_SPEED, 0 );
        }
    }
}