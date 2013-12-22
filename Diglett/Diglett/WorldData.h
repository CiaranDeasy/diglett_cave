#pragma once

#include "Chunk.h"
#include "Tile.h"

class WorldData {
public:
    // Inputs to "get" are in absolute world co-ordinates.
    Tile& getTile( int x, int y );
    Tile& getTile( sf::Vector2i in );
    Chunk& getChunk( int x, int y );
    static WorldData& getWorldData();
    ~WorldData(void);
private:
    static WorldData singleton;
    // These offsets can be added to a chunk index in absolute world
    // co-ordinates to map it to a chunk index in this object's internal array.
    int xOffset;
    int yOffset;
    // Default constructor makes simple world: half dirt, half surface.
    Chunk chunks[HORIZONTAL_CHUNKS][VERTICAL_CHUNKS];
    WorldData(void);
};