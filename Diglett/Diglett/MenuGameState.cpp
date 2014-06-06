#include "MenuGameState.h"
#include "Player.h"
#include "Physics.h"
#include "MainGameState.h"

MenuGameState::MenuGameState( 
            GameWindow *gameWindow, sf::Font& font ) : 
        inputHandler( *this ), 
        player( player ),
		font( font ) {
    this->gameWindow = gameWindow;
}

MenuGameState::~MenuGameState() {
}

void MenuGameState::gameTick() {
    handleWindowEvents();
    inputHandler.processInputs();
}

void MenuGameState::draw(sf::RenderTarget& target, sf::RenderStates states) 
        const {
    setInterfaceView( target );
}

bool MenuGameState::drawUnderlyingState() { return false; }

void MenuGameState::handleWindowEvents() {
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

void MenuGameState::launchGame() {
	gameWindow->pushNewState( new MainGameState( font, gameWindow ) );
}


MenuGameState::MenuInputHandler::MenuInputHandler( MenuGameState& gameState ) :
        gameState( gameState ) {
}
MenuGameState::MenuInputHandler::~MenuInputHandler() {
}

void MenuGameState::MenuInputHandler::processInputs() {
    std::vector<sf::Event>::const_iterator next = 
         buttonsPressed.begin();
    while( next != buttonsPressed.end() ) {
        if( next->type == sf::Event::JoystickButtonPressed && 
                next->joystickButton.button == 0 ) {
            gameState.launchGame();
        } else if( next->type == sf::Event::KeyPressed && 
                next->key.code == sf::Keyboard::Space ) {
            gameState.launchGame();
        }
        next++;
    }
}
