#pragma once
#ifndef UTILITY
#define UTILITY

#include <SFML/Graphics.hpp>

class Utility
{
public:
    static int roundToMoreNegative( float );
    static sf::Vector2i coordsGameToTile( sf::Vector2f );
    static sf::Vector2i coordsGameToChunk( sf::Vector2f );
    static sf::Vector2f coordsGameToWindow( sf::Vector2f );
    static sf::Vector2f coordsTileToWindow( sf::Vector2i );
};

#endif