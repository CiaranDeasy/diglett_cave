#include "Utility.h"
#include "Constants.h"

// Converts a point in game co-ordinates to a tile index.
sf::Vector2i Utility::coordsGameToTile( sf::Vector2f in ) {
    return sf::Vector2i( (int) floor( in.x ), (int) floor( in.y ) );
}

// Converts a point in game co-ordinates to a chunk index.
sf::Vector2i Utility::coordsGameToChunk( sf::Vector2f in ) {
    return sf::Vector2i( (int) floor( in.x / CHUNK_SIDE ), 
        (int) floor( in.y / CHUNK_SIDE ) );
}

// Converts a point in game co-ordinates to a point in window (drawing) 
// co-ordinates.
sf::Vector2f Utility::coordsGameToWindow( sf::Vector2f in ) {
    return sf::Vector2f( in.x * 64, in.y * -64 );
}

// Converts a tile index to a point in window (drawing) co-ordinates.
sf::Vector2f Utility::coordsTileToWindow( sf::Vector2i in ) {
    return coordsGameToWindow( sf::Vector2f( (float) in.x, (float) in.y ) );
}

float Utility::max( float x, float y, float z ) {
    if( x > y ) {
        if( x > z ) return x;
        else return z;
    } else {
        if( y > z ) return y;
        else return z;
    }
}