#include <iostream>
#ifndef CONSTANTS
#define CONSTANTS

const std::string WINDOW_TITLE = "Diglett";
const int PIXELS_PER_TILE = 64;
const float PLAYER_SPEED = 0.2;
const float CAMERA_ZOOM = 1.0;

// Number of chunks to store in RAM.
const int HORIZONTAL_CHUNKS = 20;
const int VERTICAL_CHUNKS = 20;

// Number of tiles in a chunk.
const int CHUNK_SIDE = 20;

#endif