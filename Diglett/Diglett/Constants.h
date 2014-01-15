#include <iostream>
#include <SFML/System.hpp>
#include "Utility.h"

#ifndef CONSTANTS
#define CONSTANTS

const int PIXELS_PER_TILE = 64;
const int PIXELS_PER_ITEM_SPRITE = 16;

// Number of tiles in a chunk.
const int CHUNK_SIDE = 20;

// Width and height of the window.
const sf::Vector2i WINDOW_RESOLUTION( 800, 600 );

#endif