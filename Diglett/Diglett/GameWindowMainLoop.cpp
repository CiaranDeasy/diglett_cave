#include "GameWindow.h"
#include "Utility.h"
#include "Constants.h"
#include "Player.h"
#include "WorldData.h"
#include <SFML/Graphics.hpp>
#include "InputHandler.h"

void GameWindow::mainLoop() {

    while( window->isOpen() ) {
        // Handle window events.
        sf::Event event;
        while( window->pollEvent( event ) ) {
            if( event.type == sf::Event::Closed ) {
                window->close();
                exit(0);
            }
        }
        // Take player movement.
        InputHandler::processInputs();
        // Draw the world.
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
                Tile nextTile = nextChunk.getTile( i, j );
                sf::Vector2i tilePosition = sf::Vector2i( 
                        nextChunk.getPosition().x + i,
                        nextChunk.getPosition().y + j );
                // Colour the origin red, for reference.
                if( tilePosition.x == 0 && tilePosition.y == 0 ) {
                    tileSprites[Tile::Dirt]->setColor( sf::Color::Red );
                    tileSprites[Tile::Dirt]->setPosition( 
                        Utility::coordsTileToWindow( tilePosition ) );
                    window->draw( *tileSprites[Tile::Dirt] );
                    tileSprites[Tile::Dirt]->setColor( sf::Color::White );
                }
                else if( nextTile.getType() == Tile::Dirt ) {
                    tileSprites[Tile::Dirt]->setPosition( 
                        Utility::coordsTileToWindow( tilePosition ) );
                    window->draw( *tileSprites[Tile::Dirt] );
                }
                else if( nextTile.getType() == Tile::Surface ) {
                    tileSprites[Tile::Surface]->setPosition( 
                        Utility::coordsTileToWindow( tilePosition ) );
                    window->draw( *tileSprites[Tile::Surface] );
                }
              }
            }
          }
        }
        playerSprite->setPosition( Utility::coordsGameToWindow( 
            Player::getPlayer().getPosition() ) );
        window->draw( *playerSprite );
        drawDebugOverlay();
        window->display();
	}
}