#include "Chunk.h"

Chunk::Chunk( Tile::Type type ) {
    for( int i = 0; i < CHUNK_SIDE; i++ ) {
        for( int j = 0; j < CHUNK_SIDE; j++ ) {
            tiles[i][j] = Tile( type );
        }
    }
}


Chunk::~Chunk( void ) {
}
