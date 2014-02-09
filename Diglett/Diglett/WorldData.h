#pragma once

#include "Chunk.h"
#include "Tile.h"
#include <array>
#include "Player.h"

class WorldData {
public:
    // Default constructor makes simple world: half dirt, half surface.
    WorldData(void);
    ~WorldData(void);

    // Inputs to "get" are in absolute world co-ordinates.
    const Tile& getTile( int x, int y ) const;
    const Tile& getTile( sf::Vector2i in ) const;
    const Chunk& getChunk( int x, int y ) const;

    // Digs the tile at the given co-ordinates and adds an item to the player's
    // inventory if appropriate.
    void digTile( int x, int y, Player& player );
private:
    static WorldData singleton;

    // Number of chunks to store in RAM.
    static const int HORIZONTAL_CHUNKS = 20;
    static const int VERTICAL_CHUNKS = 20;
    // These offsets can be added to a chunk index in absolute world
    // co-ordinates to map it to a chunk index in this object's internal array.
    int xOffset;
    int yOffset;
    std::array<std::array<Chunk, VERTICAL_CHUNKS>, HORIZONTAL_CHUNKS> chunks;
};