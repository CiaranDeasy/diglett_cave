#include <iostream>
#include <SFML/System.hpp>

#ifndef CONSTANTS
#define CONSTANTS

const std::string WINDOW_TITLE = "Diglett";
const int PIXELS_PER_TILE = 64;
const float PLAYER_SPEED = 0.2;
const float DIAG_PLAYER_SPEED = PLAYER_SPEED / 1.414; // sqrt(2)
const float CAMERA_ZOOM = 1.0;

// Number of chunks to store in RAM.
const int HORIZONTAL_CHUNKS = 20;
const int VERTICAL_CHUNKS = 20;

// Number of tiles in a chunk.
const int CHUNK_SIDE = 20;

// Minimum displacement required on analogue stick axis to accept as movement.
// Value 0-100.
const float CONTROLLER_DEADZONE = 20;

// Width and height of the window.
const sf::Vector2i WINDOW_RESOLUTION( 800, 600 );

// Path to font file for debug overlay.
const std::string DEBUG_FONT = "Fonts/segoeui.ttf";

#endif