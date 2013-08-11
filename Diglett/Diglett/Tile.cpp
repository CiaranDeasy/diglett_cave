#include "Tile.h"

Tile::Tile(void) {
    this->type = Air;
}

Tile::Tile(Type type) {
    this->type = type;
}

Tile::~Tile(void) {
}

Tile::Type Tile::getType() { return type; }