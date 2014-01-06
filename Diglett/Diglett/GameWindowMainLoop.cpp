#include "GameWindow.h"
#include "Utility.h"
#include "Constants.h"
#include "Player.h"
#include "Physics.h"
#include "WorldData.h"
#include <SFML/Graphics.hpp>
#include "InputHandler.h"

void GameWindow::mainLoop() {

    while( window->isOpen() ) {
        // Pass window events to the InputHandler.
        handleWindowEvents();
        // Take player input and pass movement to Physics to move the player 
        // appropriately.
        sf::Vector2f input = InputHandler::processInputs();
        Physics::getPhysics().updatePlayer( input );
        // Create NewItemVisuals.
        triggerNewItemVisuals();
        // Draw things!
        drawWorld();
        drawPlayer();
        drawGUI();
        window->display();
    }
}

void GameWindow::handleWindowEvents() {
    sf::Event event;
    while( window->pollEvent( event ) ) {
        if( event.type == sf::Event::Closed ) {
            window->close();
            exit(0);
        }
        if( event.type == sf::Event::JoystickButtonPressed ||
            event.type == sf::Event::KeyPressed ) {
            InputHandler::addEvent( event );
        }
    }
}

void GameWindow::drawWorld() {
    worldView.setCenter( Utility::coordsGameToWindow( 
        Player::getPlayer().getPosition() ) );
    window->setView( worldView );
    window->clear();
    sf::Vector2i playerChunk = Utility::coordsGameToChunk( 
        Player::getPlayer().getPosition() );
    for( int x = playerChunk.x - 1; x <= playerChunk.x + 1; x++ ) {
      for( int y = playerChunk.y - 1;  y <= playerChunk.y + 1; y++ ) {
        Chunk nextChunk = WorldData::getWorldData().getChunk( x, y );
        for( int i = 0; i < CHUNK_SIDE; i++ ) {
          for( int j = 0; j < CHUNK_SIDE; j++ ) {
            Tile nextTile = nextChunk.getRelativeTile( i, j );
            sf::Vector2i tilePosition = sf::Vector2i( 
                    nextChunk.getPosition().x + i,
                    nextChunk.getPosition().y + j );
            nextTile.getSprite()->setPosition( 
                Utility::coordsTileToWindow( tilePosition ) );
            window->draw( *nextTile.getSprite() );
          }
        }
      }
    }
}

void GameWindow::drawPlayer() {
    if( Player::getPlayer().isDead() ) {
       playerDeadSprite->setPosition( Utility::coordsGameToWindow( 
              Player::getPlayer().getPosition() ) );
       window->draw( *playerDeadSprite );
    } else {
       playerSprite->setPosition( Utility::coordsGameToWindow( 
              Player::getPlayer().getPosition() ) );
       window->draw( *playerSprite );
    }
}

void GameWindow::drawGUI() {
    if( showDebugOverlay ) {
        drawDebugOverlay();
    }
    if( inventoryGUI.isVisible() ) {
        window->draw( inventoryGUI );
    }
    // Display the NewItemVisuals.
    std::vector<NewItemVisual *>::iterator next = newItemVisuals.begin();
    while( next != newItemVisuals.end() ) {
        if( (*next)->isAlive() ) {
            window->draw(**next);
            (*next)->tick();
            next++;
        } else {
            // Cleanup dead NewItemVisuals.
            delete *next;
            next = newItemVisuals.erase( next );
        }
    }
    // Display the hull strength GUI.
    window->draw( hullGUI );
}
