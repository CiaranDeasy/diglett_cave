#include "PopUpGameState.h"
#include "Player.h"
#include "Physics.h"

PopUpGameState::PopUpGameState( 
        GameWindow *gameWindow, sf::Font& font, std::string message ) : 
            inputHandler( *this ), 
            popUp( message, font ) {
    this->gameWindow = gameWindow;
}

PopUpGameState::~PopUpGameState() {
}

void PopUpGameState::gameTick() {
    handleWindowEvents();
    inputHandler.processInputs();
}

void PopUpGameState::draw(sf::RenderTarget& target, sf::RenderStates states) 
        const {
    target.draw( popUp );
}

bool PopUpGameState::drawUnderlyingState() { return true; }

void PopUpGameState::handleWindowEvents() {
    sf::Event event = sf::Event();
    while( gameWindow->pollEvent( event ) ) {
        if( event.type == sf::Event::Closed ) {
            gameWindow->close();
            exit(0);
        }
        if( event.type == sf::Event::JoystickButtonPressed ||
            event.type == sf::Event::KeyPressed ) {
            inputHandler.addEvent( event );
        }
    }
}
