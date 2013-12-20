#include "InputHandler.h"
#include "Constants.h"
#include <SFML/Window.hpp>
#include "Player.h"
#include "GameWindow.h"

sf::Vector2f InputHandler::processInputs() {
    bool skipKeyboard = false;
    sf::Vector2f movement = sf::Vector2f(0, 0);

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
        movement = sf::Vector2f( 
            ( stickPositionX / 100 ) * PLAYER_SPEED, 
            ( stickPositionY / 100 ) * -PLAYER_SPEED );
        // Don't take keyboard input too.
        skipKeyboard = true;
    }

    // Keyboard movement.
    if( !skipKeyboard ) {
        bool up = sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ||
                sf::Keyboard::isKeyPressed( sf::Keyboard::W );
        bool down = sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ||
                sf::Keyboard::isKeyPressed( sf::Keyboard::S );
        bool left = sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ||
                sf::Keyboard::isKeyPressed( sf::Keyboard::A );
        bool right = sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ||
                sf::Keyboard::isKeyPressed( sf::Keyboard::D );
		if( up && left ) {
			movement = sf::Vector2f( -DIAG_PLAYER_SPEED, DIAG_PLAYER_SPEED );
        }
		else if( up && right ) {
			movement = sf::Vector2f( DIAG_PLAYER_SPEED, DIAG_PLAYER_SPEED );
        }
		else if( down && left ) {
			movement = sf::Vector2f( -DIAG_PLAYER_SPEED, -DIAG_PLAYER_SPEED );
        }
		else if( down && right ) {
			movement = sf::Vector2f( DIAG_PLAYER_SPEED, -DIAG_PLAYER_SPEED );
        }
		else if( up ) {
            movement = sf::Vector2f( 0, PLAYER_SPEED );
        }
		else if( down ) {
            movement = sf::Vector2f( 0, -PLAYER_SPEED );
        }
		else if( left) {
            movement = sf::Vector2f( -PLAYER_SPEED, 0 );
        }
		else if( right ) {
			movement = sf::Vector2f( PLAYER_SPEED, 0 );
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

    return movement;
}

void InputHandler::addEvent( sf::Event e ) {
    buttonsPressed.push_back( e );
}

// Initialise the list of button events to an empty vector.
std::vector<sf::Event> InputHandler::buttonsPressed = std::vector<sf::Event>();