#include "ShopGameState.h"
#include "Player.h"

ShopGameState::ShopGameState( 
        GameWindow *gameWindow, sf::Font& font, Player& player ) : 
            inputHandler( *this ),
            shopGUI( font, player.getInventory() ),
            player( player ) {
    this->gameWindow = gameWindow;
}

ShopGameState::~ShopGameState() {
}

void ShopGameState::gameTick() {
    handleWindowEvents();
    inputHandler.processInputs();
}

void ShopGameState::draw(sf::RenderTarget& target, sf::RenderStates states) 
        const {
    setInterfaceView( target );
    target.draw( shopGUI );
}

bool ShopGameState::drawUnderlyingState() { return true; }

void ShopGameState::sell() {
    std::vector<Item *> contents = player.getInventory().getContents();
    std::vector<Item *>::iterator next = contents.begin();
    while( next != contents.end() ) {
        player.addMoney( (*next)->getValue() );
        next++;
    }
    player.getInventory().clear();
}

void ShopGameState::handleWindowEvents() {
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

ShopGameState::ShopInputHandler::ShopInputHandler( ShopGameState& gameState ) 
        : gameState( gameState ) {
    }
ShopGameState::ShopInputHandler::~ShopInputHandler() {}

void ShopGameState::ShopInputHandler::processInputs() {
    // Process events passed from the GameWindow.
    // These events will be keys or buttons being pressed.
    for( int i = 0; i < InputHandler::buttonsPressed.size(); i++ ) {
        sf::Event& e = buttonsPressed[i];
        // Joystick buttons.
        if( e.type == sf::Event::JoystickButtonPressed ) {
          if( e.joystickButton.button == 1 ) {
              gameState.dead = true;
          } else if( e.joystickButton.button == 0 ) {
              gameState.sell();
          }
        }
        // Keyboard keys.
        else if( e.type == sf::Event::KeyPressed ) {
          if( e.key.code == sf::Keyboard::Escape ) {
              gameState.dead = true;
          } else if( e.key.code == sf::Keyboard::Space ) {
              gameState.sell();
          }
        }
    }

    buttonsPressed.clear();
}
