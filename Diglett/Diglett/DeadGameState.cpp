#include "DeadGameState.h"
#include "Player.h"
#include "Physics.h"
#include "Resources.h"

DeadGameState::DeadGameState( 
            GameWindow *gameWindow, Player& player ) : 
        inputHandler( *this ), 
        deadNotification( DEATH_MESSAGE, Resources::getResources().getFont() ),
        player( player ) {
    this->gameWindow = gameWindow;
}

DeadGameState::~DeadGameState() {
}

void DeadGameState::gameTick( float deltaTime ) {
    handleWindowEvents();
    inputHandler.processInputs();
}

void DeadGameState::draw(sf::RenderTarget& target, sf::RenderStates states) 
        const {
    setInterfaceView( target );
    target.draw( deadNotification );
}

void DeadGameState::respawn() {
    // Reset the player's hull to max, and empty their inventory.
    player.respawn();
    // Reset the player's velocity to zero.
    Physics::getPhysics().reset();
    // Mark this state as dead so the MainGameState takes over again.
    this->dead = true;
}

bool DeadGameState::drawUnderlyingState() { return true; }

const std::string DeadGameState::DEATH_MESSAGE = 
        "You have died. Press SPACE or CONTROLLER \"A\" to respawn.";

void DeadGameState::handleWindowEvents() {
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

DeadGameState::DeadInputHandler::DeadInputHandler( DeadGameState& gameState ) :
        gameState( gameState ) {
}
DeadGameState::DeadInputHandler::~DeadInputHandler() {
}

void DeadGameState::DeadInputHandler::processInputs() {
    std::vector<sf::Event>::const_iterator next = 
         buttonsPressed.begin();
    while( next != buttonsPressed.end() ) {
        if( next->type == sf::Event::JoystickButtonPressed && 
                next->joystickButton.button == 0 ) {
            gameState.respawn();
        } else if( next->type == sf::Event::KeyPressed && 
                next->key.code == sf::Keyboard::Space ) {
            gameState.respawn();
        }
        next++;
    }
}
