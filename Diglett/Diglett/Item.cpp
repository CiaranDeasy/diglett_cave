#include "Item.h"
#include "GameWindow.h"
#include "Constants.h"

void Item::initialiseTypes() {
    types.push_back( ItemType( "NULL", NULL ) ); // Indicates no item.
    types.push_back( ItemType( "Gold", 
            GameWindow::makeSquareSprite( 
                sf::Color( 255, 215, 0, 255 ), PIXELS_PER_ITEM_SPRITE ) ) );
}

Item::Item( int type ) {
    this->type = type;
}

Item::~Item(void) {}

std::string Item::getName() {
    return lookupType( this->type ).getName();
}

sf::Sprite *Item::getSprite() {
    return lookupType( this->type ).getSprite();
}

ItemType& Item::lookupType( int id ) {
    return types[id];
}

std::vector<ItemType> Item::types = std::vector<ItemType>();