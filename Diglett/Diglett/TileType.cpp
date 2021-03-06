#include "TileType.h"
#include "Constants.h"

TileType::TileType(void) {
    // Not a valid constructor.
}

TileType::TileType( std::string name, sf::Sprite *sprite, bool diggable, 
                   bool solid, int item ) {
     this->name = name;
     this->sprite = sprite;
     sprite->setOrigin( 0, (float) PIXELS_PER_TILE );
     this->diggable = diggable;
     this->solid = solid;
     this->item = item;
}


TileType::~TileType(void) {
}

sf::Sprite *TileType::getSprite() { return sprite; }

bool TileType::isDiggable() { return diggable; }

bool TileType::isSolid() { return solid; }

Item *TileType::createItem() { return new Item( item ); }