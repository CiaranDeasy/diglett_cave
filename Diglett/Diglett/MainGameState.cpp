#include "MainGameState.h"
#include "Physics.h"
#include "GameWindow.h"
#include "Utility.h"
#include "WorldData.h"
#include <sstream>
#include "DeadGameState.h"
#include "ShopGameState.h"
#include "Shop.h"

MainGameState::MainGameState( sf::Font& font, GameWindow *gameWindow ) : 
        GameState(),
        font( font ), 
        inputHandler( *this ),
        tutorials( gameWindow, font ),
        GUI( font, Player::getPlayer().getInventory() ),
        world( Player::getPlayer() ) {
    createSprites();
    this->gameWindow = gameWindow;
}

MainGameState::~MainGameState() {
}

void MainGameState::setWorldView( sf::RenderTarget& target ) {
    sf::Vector2f centerPoint = 
        ( Utility::coordsGameToWindow( Player::getPlayer().getPosition() ) );
    sf::View worldView = sf::View( centerPoint, 
            sf::Vector2f( target.getSize().x, target.getSize().y ) );
    worldView.zoom( CAMERA_ZOOM );
    target.setView( worldView );
}

void MainGameState::gameTick() {
    // Pass window events to the InputHandler.
    handleWindowEvents();
    // Process the player's input.
    inputHandler.processInputs();
    // Advance the GUI.
    GUI.tick();
    // Test if the player is dead.
    if( Player::getPlayer().isDead() ) {
        GameState *deadGameState = new DeadGameState( gameWindow, font );
        gameWindow->pushNewState( deadGameState );
    }
    // Test for tutorial triggers.
    tutorials.testTriggers( world );
}
    
void MainGameState::draw( 
        sf::RenderTarget& target, sf::RenderStates states ) const {
    setWorldView( target );
    target.draw( world );
    drawPlayer( target );
    setInterfaceView( target );
    target.draw( GUI );
}

bool MainGameState::drawUnderlyingState() { return false; }

const float MainGameState::CAMERA_ZOOM = 1.0;

void MainGameState::createSprites() {
    playerSprite = GameWindow::makeCircleSprite( sf::Color::Magenta );
    playerSprite->setOrigin( 32, 32 );
    playerDeadSprite = GameWindow::makeCircleSprite( sf::Color::Red );
    playerDeadSprite->setOrigin( 32, 32 );
}

void MainGameState::handleWindowEvents() {
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

void MainGameState::drawPlayer( sf::RenderTarget& target ) const {
    setWorldView( target );
    if( Player::getPlayer().isDead() ) {
       playerDeadSprite->setPosition( Utility::coordsGameToWindow( 
              Player::getPlayer().getPosition() ) );
       target.draw( *playerDeadSprite );
    } else {
       playerSprite->setPosition( Utility::coordsGameToWindow( 
              Player::getPlayer().getPosition() ) );
       target.draw( *playerSprite );
    }
}

void MainGameState::openShop() {
    gameWindow->pushNewState( new ShopGameState( gameWindow, font ) );
}
