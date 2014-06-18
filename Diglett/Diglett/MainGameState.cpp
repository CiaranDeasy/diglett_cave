#include "MainGameState.h"
#include "Physics.h"
#include "GameWindow.h"
#include "Utility.h"
#include "WorldData.h"
#include <sstream>
#include "DeadGameState.h"
#include "ShopGameState.h"
#include "Shop.h"
#include "Resources.h"

MainGameState::MainGameState( GameWindow *gameWindow ) : 
        GameState(),
        player(), 
        inputHandler( *this ),
        tutorials( gameWindow ),
        GUI( player ),
        world( player ) {
    createSprites();
    this->gameWindow = gameWindow;
}

MainGameState::~MainGameState() {
}

void MainGameState::setWorldView( sf::RenderTarget& target ) const {
    sf::Vector2f centerPoint = 
        ( Utility::coordsGameToWindow( player.getPosition() ) );
    sf::View worldView = sf::View( centerPoint, sf::Vector2f( 
		    (float) target.getSize().x, (float) target.getSize().y ) );
    worldView.zoom( CAMERA_ZOOM );
    target.setView( worldView );
}

void MainGameState::gameTick( float deltaTime ) {
    // Pass window events to the InputHandler.
    handleWindowEvents();
    // Process the player's input.
    inputHandler.processInputs( deltaTime );
    // Advance the GUI.
    GUI.tick();
    // Test if the player is dead.
    if( player.isDead() ) {
        GameState *deadGameState = 
                new DeadGameState( gameWindow, player );
        gameWindow->pushNewState( deadGameState );
    }
    // Test for tutorial triggers.
    tutorials.testTriggers( world, player );
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
    playerSprite = 
		    new sf::Sprite( Resources::getResources().getPlayerTexture() );
    playerSprite->setOrigin( 32, 32 );
    playerDeadSprite =  
		    new sf::Sprite( Resources::getResources().getPlayerDeadTexture() );
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
    if( player.isDead() ) {
       playerDeadSprite->setPosition( Utility::coordsGameToWindow( 
              player.getPosition() ) );
       target.draw( *playerDeadSprite );
    } else {
       playerSprite->setPosition( Utility::coordsGameToWindow( 
              player.getPosition() ) );
       target.draw( *playerSprite );
    }
}
