#include "DismissInputHandler.h"

DismissInputHandler::DismissInputHandler( GameState& gameState ) 
        : gameState( gameState ) {
}

DismissInputHandler::~DismissInputHandler() {
}

void DismissInputHandler::processInputs() {
    // Process events passed from the GameWindow.
    // These events will be keys or buttons being pressed.
    for( unsigned int i = 0; i < InputHandler::buttonsPressed.size(); i++ ) {
        sf::Event& e = buttonsPressed[i];
        // Joystick buttons.
        if( e.type == sf::Event::JoystickButtonPressed ) {
          if( e.joystickButton.button == 0 ) {
              gameState.dead = true;
          }
        }
        // Keyboard keys.
        else if( e.type == sf::Event::KeyPressed ) {
          if( e.key.code == sf::Keyboard::Space ) {
              gameState.dead = true;
          }
        }
    }

    // Clear all the events.
    buttonsPressed.clear();
}