#pragma once
#include "Tile.h"
const int CHUNK_SIDE = 20;

class Chunk {
    Tile tiles[CHUNK_SIDE][CHUNK_SIDE];
public:
    // Constructor which takes a type of tile and makes a chunk consisting 
    // entirely of tiles of that type.
    Chunk( Tile::Type );
    ~Chunk( void );

    // Default constructor not supported.
    // Present to keep arrays happy.
    Chunk( void );
private:
};

