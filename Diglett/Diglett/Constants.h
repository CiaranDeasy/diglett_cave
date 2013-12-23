#include <iostream>
#include <SFML/System.hpp>
#include "Utility.h"

#ifndef CONSTANTS
#define CONSTANTS

const std::string WINDOW_TITLE = "Diglett";
const int PIXELS_PER_TILE = 64;
const int PIXELS_PER_ITEM_SPRITE = 16;
const float PLAYER_SPEED = 0.008;
const float PLAYER_MAX_SPEED = 0.2;
const float DIAG_PLAYER_SPEED = PLAYER_SPEED / 1.414; // sqrt(2)
const float GRAVITY_STRENGTH = 0.003;
const float HORIZONTAL_AIR_RESISTANCE = 0.05;
const float VERTICAL_AIR_RESISTANCE = 0.001;
const float MINIMUM_VELOCITY = 0.01;
const float BOUNCE_FACTOR = 0.2;
const float CAMERA_ZOOM = 1.0;
const float PLAYER_MASS = 1.0;
const int MAX_INVENTORY = 32;

// Number of ticks the player must spend on the ground before allowed to dig.
const int DIG_DELAY = 15;

// Number of ticks it takes the player to dig a block.
const int DIG_STEPS = 60;

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

// Position in window of inventory GUI.
const sf::Vector2i INVENTORY_POSITION = sf::Vector2i( 25, 25 );

// Number of pixels between edges of inventory GUI and its contents.
const int INVENTORY_BORDER = 10;

// Number of items that should be displayed vertically in the inventory GUI.
const int INVENTORY_ITEMS_PER_COL = 8;

// Size in pixels of a single entry in the inventory.
const sf::Vector2i INVENTORY_ENTRY_SIZE = sf::Vector2i( 128, 19 );

// Number of pixels separating an item sprite and its name.
const int INVENTORY_SPRITE_SEPARATION = 6;

// Size of text in inventory.
const int INVENTORY_TEXT_SIZE = 12;

// Path to font file for debug overlay.
const std::string DEBUG_FONT = "Fonts/segoeui.ttf";

#endif