#include "InputHandler.h"

InputHandler::InputHandler(void) {
    // Initialise the list of button events to an empty vector.
    buttonsPressed = std::vector<sf::Event>();
}

InputHandler::~InputHandler(void) {
}

void InputHandler::addEvent( sf::Event e ) {
    buttonsPressed.push_back( e );
}