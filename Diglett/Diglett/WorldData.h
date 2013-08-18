#pragma once

#include "Chunk.h"
#include "Tile.h"

class WorldData {
public:
    Chunk getChunk( int x, int y );
    // Default constructor makes simple world: half dirt, half surface.
    WorldData(void);
    ~WorldData(void);
private:
    // These offsets can be added to a chunk index in absolute world
    // co-ordinates to map it to a chunk index in this object's internal array.
    int xOffset;
    int yOffset;
    Chunk chunks[HORIZONTAL_CHUNKS][VERTICAL_CHUNKS];
};