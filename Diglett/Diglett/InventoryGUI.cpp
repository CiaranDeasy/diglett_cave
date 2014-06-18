#include "InventoryGUI.h"
#include "Player.h"
#include "GameWindow.h"
#include "Constants.h"
#include "Resources.h"

InventoryGUI::InventoryGUI( Inventory<Item *>& inventory ) : 
        inventory(inventory) {
    visible = false;
    position = DEFAULT_POSITION;
    border = DEFAULT_BORDER;
    itemsPerCol = DEFAULT_ITEMS_PER_COL;
    entrySize = DEFAULT_ENTRY_SIZE;
    spriteSeparation = DEFAULT_SPRITE_SEPARATION;
    textSize = DEFAULT_TEXT_SIZE;
    backgroundColor = DEFAULT_BACKGROUND_COLOR;
    textColor = DEFAULT_TEXT_COLOR;
}

InventoryGUI::~InventoryGUI(void) {
}

void InventoryGUI::toggle() {
    visible = !visible;
}

void InventoryGUI::draw( 
        sf::RenderTarget& target, 
        sf::RenderStates states ) const {
    sf::Vector2i absPosition = position;
    if( absPosition.x < 0 ) absPosition.x = target.getSize().x + absPosition.x;
    if( absPosition.y < 0 ) absPosition.y = target.getSize().y + absPosition.y;
    std::vector<Item *> contents = inventory.getContents();
    // Draw the inventory background.
    sf::RectangleShape *inventoryBackground = 
            makeInventoryBackground( contents );
    inventoryBackground->setPosition( sf::Vector2f( absPosition ) );
    target.draw( *inventoryBackground );
    delete inventoryBackground;
    for( int i = 0; i < inventory.getCurrentSize(); i++ ) {
        // Calculate the position of the sprite.
        float spritePositionX = (float) 
			    ( absPosition.x + border + ( i / itemsPerCol ) * entrySize.x );
        float spritePositionY = (float)
			    ( absPosition.y + border + ( i % itemsPerCol ) * entrySize.y );
        // Draw the sprite.
        contents[i]->getSprite()->setPosition( 
                spritePositionX, spritePositionY );
        target.draw( *contents[i]->getSprite() );
        // Make the text.
        sf::Text text;
        text.setFont( Resources::getResources().getFont() );
        text.setCharacterSize( textSize );
        text.setColor( textColor );
        text.setString( contents[i]->getName() );
        // Position the text.
        text.setPosition(
          spritePositionX + PIXELS_PER_ITEM_SPRITE + spriteSeparation, 
          spritePositionY + (PIXELS_PER_ITEM_SPRITE / 2) - (textSize / 2) );
        // Draw the text.
        target.draw( text );
    }
}

bool InventoryGUI::isVisible() const { return visible; }

const sf::Vector2i InventoryGUI::DEFAULT_POSITION = sf::Vector2i( 25, 25 );
const int InventoryGUI::DEFAULT_BORDER = 10;
const unsigned int InventoryGUI::DEFAULT_ITEMS_PER_COL = 8;
const sf::Vector2i InventoryGUI::DEFAULT_ENTRY_SIZE = 
        sf::Vector2i( 128, 19 );
const int InventoryGUI::DEFAULT_SPRITE_SEPARATION = 6;
const int InventoryGUI::DEFAULT_TEXT_SIZE = 12;
const sf::Color InventoryGUI::DEFAULT_BACKGROUND_COLOR = 
        sf::Color( 0, 0, 0, 207 );
const sf::Color InventoryGUI::DEFAULT_TEXT_COLOR = 
        sf::Color( 255, 255, 255, 255 );

sf::RectangleShape *InventoryGUI::makeInventoryBackground( 
            std::vector<Item *>& contents ) const {
    float sizeX = (float) ( ((( (contents.size() - 1)/ itemsPerCol )
            + 1 ) * entrySize.x ) + 2 * border );
    float sizeY;

    if( contents.size() <= itemsPerCol ) {
        sizeY = (float) ( ( contents.size() * entrySize.y ) + 2 * border );
    } else {
        sizeY = (float) ( ( itemsPerCol * entrySize.y ) + 2 * border );
    }

    sf::RectangleShape *background = 
        new sf::RectangleShape( sf::Vector2f( sizeX, sizeY ) );
    background->setFillColor( backgroundColor );

    return background;
}
