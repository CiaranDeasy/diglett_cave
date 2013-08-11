#pragma once
#include "Tile.h"
const int CHUNK_SIDE = 20;

class Chunk {
    Tile tiles[CHUNK_SIDE][CHUNK_SIDE];
public:
    // Banish this sick filth
    enum Type {
        Overworld,
        Underworld
    };
    Chunk( void );
    Chunk( Type );
    ~Chunk( void );
};

