#include "WorldData.h"
#include "Chunk.h"
#include "Tile.h"

Chunk WorldData::getChunk( int x, int y ) {
    return chunks[x + xOffset][ y + yOffset];
}

WorldData::WorldData(void) {
    xOffset = 10;
    yOffset = 10;
    for( int i = 0; i < 20; i++ ) {
        for( int j = 0; j < 10; j++ ) {
            chunks[i][j] = Chunk::Chunk( 
                    sf::Vector2i( ( i - xOffset ) * CHUNK_SIDE, 
                    ( j - yOffset ) * CHUNK_SIDE ),
                    Tile::Type::Dirt );
            chunks[i][j+10] = Chunk::Chunk( 
                    sf::Vector2i( ( i - xOffset ) * CHUNK_SIDE, 
                    ( j + 10 - yOffset ) * CHUNK_SIDE ),
                    Tile::Type::Surface );
        }
    }
}

WorldData::~WorldData(void) {
}