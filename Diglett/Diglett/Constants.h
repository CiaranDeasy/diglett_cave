#include <iostream>
#include <SFML/System.hpp>
#include "Utility.h"

#ifndef CONSTANTS
#define CONSTANTS

const std::string WINDOW_TITLE = "Diglett";
const int PIXELS_PER_TILE = 64;
const float PLAYER_SPEED = 0.01;
const float PLAYER_MAX_SPEED = 0.2;
const float DIAG_PLAYER_SPEED = PLAYER_SPEED / 1.414; // sqrt(2)
const float GRAVITY_STRENGTH = 0.004;
const float HORIZONTAL_AIR_RESISTANCE = 0.005;
const float VERTICAL_AIR_RESISTANCE = 0.001;
const float MINIMUM_VELOCITY = 1.25 * Utility::max( 
        GRAVITY_STRENGTH, HORIZONTAL_AIR_RESISTANCE, VERTICAL_AIR_RESISTANCE );
const float CAMERA_ZOOM = 1.0;
const float PLAYER_MASS = 1.0;

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