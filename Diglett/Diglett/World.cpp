#include "World.h"
#include "Utility.h"
#include "Chunk.h"
#include "WorldData.h"
#include "InteractiveEntity.h"
#include "Shop.h"

World::World( Player& player ) : player( player ), worldData() {
    interactiveEntities.push_back( new Shop() );
}

World::~World(void) {
}

void World::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.clear();
    sf::Vector2i playerChunk = Utility::coordsGameToChunk( 
        player.getPosition() );
    for( int x = playerChunk.x - 1; x <= playerChunk.x + 1; x++ ) {
      for( int y = playerChunk.y - 1;  y <= playerChunk.y + 1; y++ ) {
        Chunk nextChunk = worldData.getChunk( x, y );
        for( int i = 0; i < CHUNK_SIDE; i++ ) {
          for( int j = 0; j < CHUNK_SIDE; j++ ) {
            Tile nextTile = nextChunk.getRelativeTile( i, j );
            sf::Vector2i tilePosition = sf::Vector2i( 
                    nextChunk.getPosition().x + i,
                    nextChunk.getPosition().y + j );
            nextTile.getSprite()->setPosition( 
                Utility::coordsTileToWindow( tilePosition ) );
            target.draw( *nextTile.getSprite() );
          }
        }
      }
    }
    std::vector<InteractiveEntity *>::const_iterator next = 
            interactiveEntities.begin();
    while( next != interactiveEntities.end() ) {
        target.draw( **next );
        next++;
    }
}

void World::interact( GameWindow *gameWindow, sf::Font& font ) {
    std::vector<InteractiveEntity *>::iterator next = 
            interactiveEntities.begin();
    while( next != interactiveEntities.end() ) {
        sf::Vector2f playerPos = player.getPosition();
        sf::Vector2f entity = (*next)->getPosition();
        if( playerPos.x > entity.x - 1 && playerPos.x < entity.x + 1 && 
                playerPos.y > entity.y - 1 && playerPos.y < entity.y + 1 ) {
            (*next)->interact( gameWindow, font, player );
            next++;
        }
        else {
            next++;
        }
    }
}

const Tile& World::getTile( int x, int y ) const {
    return worldData.getTile( x, y );
}

const Tile& World::getTile( sf::Vector2i in ) const {
    return worldData.getTile( in.x, in.y );
}

void World::digTile( sf::Vector2i tileCoords, Player& player ) {
    worldData.digTile( tileCoords.x, tileCoords.y, player );
}
