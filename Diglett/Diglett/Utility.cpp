#include "Utility.h"
#include "Constants.h"

// For co-ordinate conversion from world co-ordinates to chunk co-ordinates, we
// need to always round towards negative infinity. C++ always rounds towards 
// zero. Today we correct that mistake.
int Utility::roundToMoreNegative( float f ) {
    if( f > 0 ) return (int) f;
    else return ( (int) f ) - 1;
}

// Converts a point in game co-ordinates to a tile index.
sf::Vector2i Utility::coordsGameToTile( sf::Vector2f in ) {
    return sf::Vector2i( roundToMoreNegative( in.x ), 
            roundToMoreNegative( in.y ) );
}

// Converts a point in game co-ordinates to a chunk index.
sf::Vector2i Utility::coordsGameToChunk( sf::Vector2f in ) {
    return sf::Vector2i( roundToMoreNegative( in.x / CHUNK_SIDE ), 
            roundToMoreNegative( in.y / CHUNK_SIDE ) );
}

// Converts a point in game co-ordinates to a point in window (drawing) 
// co-ordinates.
sf::Vector2f Utility::coordsGameToWindow( sf::Vector2f in ) {
    return sf::Vector2f( in.x * 64, in.y * -64 );
}

// Converts a tile index to a point in window (drawing) co-ordinates.
sf::Vector2f Utility::coordsTileToWindow( sf::Vector2i in ) {
    return coordsGameToWindow( sf::Vector2f( in.x, in.y ) );
}
