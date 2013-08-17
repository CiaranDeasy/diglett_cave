#include "Chunk.h"

sf::Vector2i Chunk::getPosition() {
    return position;
}

Tile Chunk::getTile( int x, int y ) {
    return tiles[x][y];
}

Chunk::Chunk( sf::Vector2i pos, Tile::Type type ) {
    position = pos;
    for( int i = 0; i < CHUNK_SIDE; i++ ) {
        for( int j = 0; j < CHUNK_SIDE; j++ ) {
            tiles[i][j] = Tile( type );
        }
    }
}

Chunk::Chunk( void ) {
    // Not a valid constructor. 
}

Chunk::~Chunk( void ) {
}
