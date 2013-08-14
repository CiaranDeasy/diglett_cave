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
private:
    // Default constructor not supported.
    Chunk( void );
};

