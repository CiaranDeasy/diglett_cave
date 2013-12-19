#include "InputHandler.h"
#include "Constants.h"
#include <SFML/Window.hpp>
#include "Player.h"
#include "GameWindow.h"

#define TAN30 0.57735
#define TAN60 1.73205

void InputHandler::processInputs() {
    bool skipKeyboard = false;

    // Controller movement.
    float stickPositionX = 
        sf::Joystick::getAxisPosition( 0, sf::Joystick::X );
    float stickPositionY = 
        sf::Joystick::getAxisPosition( 0, sf::Joystick::Y );
    // If the stick is outside the deadzone, move the player.
    if( stickPositionX > CONTROLLER_DEADZONE || 
        stickPositionX < -CONTROLLER_DEADZONE || 
        stickPositionY > CONTROLLER_DEADZONE ||
        stickPositionY < -CONTROLLER_DEADZONE ) {

        // Classify direction of movement.
        directionOfMovement = classifyDirectionOfMovement(
                stickPositionX, stickPositionY );

	    Player::getPlayer().move( 
            ( stickPositionX / 100 ) * PLAYER_SPEED, 
            ( stickPositionY / 100 ) * -PLAYER_SPEED );
        // Don't take keyboard input too.
        skipKeyboard = true;
    }

    // Keyboard movement.
    if( !skipKeyboard ) {
        bool up = sf::Keyboard::isKeyPressed( sf::Keyboard::Up );
        bool down = sf::Keyboard::isKeyPressed( sf::Keyboard::Down );
        bool left = sf::Keyboard::isKeyPressed( sf::Keyboard::Left );
        bool right = sf::Keyboard::isKeyPressed( sf::Keyboard::Right );
		if( up && left ) {
            directionOfMovement = Northwest;
			Player::getPlayer().move( -DIAG_PLAYER_SPEED, DIAG_PLAYER_SPEED );
        }
		else if( up && right ) {
            directionOfMovement = Northeast;
			Player::getPlayer().move( DIAG_PLAYER_SPEED, DIAG_PLAYER_SPEED );
        }
		else if( down && left ) {
            directionOfMovement = Southwest;
			Player::getPlayer().move( -DIAG_PLAYER_SPEED, -DIAG_PLAYER_SPEED );
        }
		else if( down && right ) {
            directionOfMovement = Southeast;
			Player::getPlayer().move( DIAG_PLAYER_SPEED, -DIAG_PLAYER_SPEED );
        }
		else if( up ) {
            directionOfMovement = North;
			Player::getPlayer().move( 0, PLAYER_SPEED );
        }
		else if( down ) {
            directionOfMovement = South;
			Player::getPlayer().move( 0, -PLAYER_SPEED );
        }
		else if( left) {
            directionOfMovement = West;
			Player::getPlayer().move( -PLAYER_SPEED, 0 );
        }
		else if( right ) {
            directionOfMovement = East;
			Player::getPlayer().move( PLAYER_SPEED, 0 );
        }
    }

    // Process events passed from the GameWindow.
    // These events will be keys or buttons being pressed.
    for( int i = 0; i < buttonsPressed.size(); i++ ) {
        sf::Event& e = buttonsPressed[i];
        // Joystick buttons.
        if( e.type == sf::Event::JoystickButtonPressed ) {
          if( e.joystickButton.button == 6 ) {
              GameWindow::getGameWindow()->toggleDebugOverlay();
          }
        }
        // Keyboard keys.
        else if( e.type == sf::Event::KeyPressed ) {
          if( e.key.code == sf::Keyboard::F3 ) {
              GameWindow::getGameWindow()->toggleDebugOverlay();
          }
        }
    }

    // Clear all the events.
    buttonsPressed.clear();
}

void InputHandler::addEvent( sf::Event e ) {
    buttonsPressed.push_back( e );
}

InputHandler::Direction InputHandler::classifyDirectionOfMovement(
        float stickPositionX, float stickPositionY) {

    // Handle the X=0 case.
    if( stickPositionX == 0 ) {
        if( stickPositionY > 0 ) {
            return South;
        } else return North;
    }

    float tan = stickPositionY/stickPositionX;
    // Take absolute value.
    tan = (tan >= 0) ? tan : (0 - tan);
    if( stickPositionX > 0 ) {
        if( stickPositionY >= 0 ) {
            // South-east quadrant.
            if( tan < TAN30 ) return Eastsoutheast;
            else if( tan > TAN60 ) return Southsoutheast;
            else return Southeast;
        } else {
            // North-east quadrant.
            if( tan < TAN30 ) return Eastnortheast;
            else if( tan > TAN60 ) return Northnortheast;
            else return Northeast;
        }
    } else {
        if( stickPositionY >= 0 ) {
            // South-west quadrant.
            if( tan < TAN30 ) return Westsouthwest;
            else if( tan > TAN60 ) return Southsouthwest;
            else return Southwest;
        } else {
            // North-west quadrant.
            if( tan < TAN30 ) return Westnorthwest;
            else if( tan > TAN60 ) return Northnorthwest;
            else return Northwest;
        }
    }
}

InputHandler::Direction InputHandler::directionOfMovement = North;

// Initialise the list of button events to an empty vector.
std::vector<sf::Event> InputHandler::buttonsPressed = std::vector<sf::Event>();