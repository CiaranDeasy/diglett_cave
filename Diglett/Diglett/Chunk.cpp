#include "Chunk.h"


Chunk::Chunk( void ) {
    // Don't call this. Just don't.
}

Chunk::Chunk( Chunk::Type type ) {
    for( int i = 0; i < CHUNK_SIDE; i++ ) {
        for( int j = 0; j < CHUNK_SIDE; j++ ) {
            tiles[i][j] = Tile( Tile::Type::Dirt );
        }
    }
}


Chunk::~Chunk( void )
{
}
