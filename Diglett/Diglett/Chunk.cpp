#include "Chunk.h"


sf::Vector2i Chunk::getPosition() {
    return position;
}

const Tile& Chunk::getRelativeTile( int x, int y ) const {
    return tiles[x][y];
}

const Tile& Chunk::getAbsoluteTile( int x, int y ) const {
    return tiles[x-position.x][y-position.y];
}

void Chunk::digAbsoluteTile( int x, int y, Player& player ) {
    tiles[x-position.x][y-position.y].dig( player );
}

Chunk::Chunk( sf::Vector2i pos, int type ) {
    position = pos;
    for( int i = 0; i < CHUNK_SIDE; i++ ) {
        for( int j = 0; j < CHUNK_SIDE; j++ ) {
#ifdef DIGLETT_DEBUG
            // Hack in some gold tiles for quicker testing.
            if( j == CHUNK_SIDE-1 ) tiles[i][j] = Tile( 3 );
            else 
#endif
            if(type == 1)
                tiles[i][j] = Tile( type );
            else {
                tiles[i][j] = Chunk::randomTileType(position.y);
            }
        }
    }
}

Tile Chunk::randomTileType(int depth){
    //Randomise the chunks which are below surface level, with the ore rate being a funciton of depth
    int i = rand() % 20;
    if ( i <= 1 )
        return Tile( 0 ); //Air
    else if ( i > 1 && i < Chunk::scaledDepth(depth) )
        return Tile( 2 ); //dirt
    else
        return Tile( 3 ); //gold
}

int Chunk::scaledDepth( int depth ){
    if(depth >= -20)
        return 20;
    else if(depth > -80)
        return 19;
    else if(depth > -120)
        return 18;
    else
        return 17;
}

Chunk::Chunk( void ) {
    // Not a valid constructor. 
}

Chunk::~Chunk( void ) {
}
