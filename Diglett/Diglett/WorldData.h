#pragma once

#include "Chunk.h"
#include "Tile.h"

const int HORIZONTAL_CHUNKS = 20;
const int VERTICAL_CHUNKS = 20;

class WorldData {
    // These offsets can be added to a chunk index in absolute world
    // co-ordinates to map it to a chunk in the subset that is currently stored
    // in WorldData.
    int xOffset;
    int yOffset;
    Chunk chunks[HORIZONTAL_CHUNKS][VERTICAL_CHUNKS];
public:
    // Default constructor makes simple world: half dirt, half surface.
    WorldData(void);
    ~WorldData(void);
};

