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

void Tile::dig() { type = Air; }

bool Tile::diggable(Tile t) {
    return diggableByType[t.getType()];
}

bool Tile::diggableByType[Count] = {
    true, // Dirt
    false, // Air
    false // Surface
};