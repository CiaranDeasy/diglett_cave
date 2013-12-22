#include "Chunk.h"

sf::Vector2i Chunk::getPosition() {
    return position;
}

Tile& Chunk::getRelativeTile( int x, int y ) {
    return tiles[x][y];
}

Tile& Chunk::getAbsoluteTile( int x, int y ) {
    return tiles[x-position.x][y-position.y];
}

Chunk::Chunk( sf::Vector2i pos, int type ) {
    position = pos;
    for( int i = 0; i < CHUNK_SIDE; i++ ) {
        for( int j = 0; j < CHUNK_SIDE; j++ ) {
            // MASSIVE HACK!!! TODO: REMOVE!!!
            if( i == 5 && j == 5 ) tiles[i][j] = Tile( 3 ); // Gold
            else tiles[i][j] = Tile( type );
        }
    }
}

Chunk::Chunk( void ) {
    // Not a valid constructor. 
}

Chunk::~Chunk( void ) {
}
