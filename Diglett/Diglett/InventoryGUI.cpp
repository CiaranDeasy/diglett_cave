#include "InventoryGUI.h"
#include "Player.h"
#include "GameWindow.h"

InventoryGUI::InventoryGUI(void) {
    visible = false;
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
    if( visible ) {
        visible = false;
    } else {
        visible = true;
        expectedInventorySize = Player::getPlayer().getInventory().size();
    }
}

void InventoryGUI::draw( 
        sf::RenderTarget& target, 
        sf::RenderStates states ) const {
    std::vector<Item *> inventory = Player::getPlayer().getInventory();
    // Set up the view.
    // TODO: make the view dependent on the states input.
    sf::View view = sf::View( sf::Vector2f( 0.0f, 0.0f ), 
            sf::Vector2f( target.getSize().x, target.getSize().y ) );
    view.setViewport( sf::FloatRect( 0.0f, 0.0f, 1.0f, 1.0f ) );
    view.zoom( 1.0 );
    target.setView( view );
    // Draw the inventory background.
    sf::RectangleShape *inventoryBackground = makeInventoryBackground();
    target.draw( *inventoryBackground );
    delete inventoryBackground;
    for( int i = 0; i < inventory.size(); i++ ) {
        // Calculate the position of the sprite.
        int spritePositionX = 
            -(WINDOW_RESOLUTION.x /2) + INVENTORY_POSITION.x + border
                + ( i / itemsPerCol ) * entrySize.x;
        int spritePositionY =
            -(WINDOW_RESOLUTION.y /2) + INVENTORY_POSITION.y + border
                + ( i % itemsPerCol ) * entrySize.y;
        // Draw the sprite.
        inventory[i]->getSprite()->setPosition( 
                spritePositionX, spritePositionY );
        target.draw( *inventory[i]->getSprite() );
        // Make the text.
        sf::Text text;
        // TODO: make the font internal to InventoryGUI.
        text.setFont( GameWindow::getGameWindow()->getFont() );
        text.setCharacterSize( textSize );
        text.setColor( textColor );
        text.setString( inventory[i]->getName() );
        // Position the text.
        text.setPosition(
          spritePositionX + PIXELS_PER_ITEM_SPRITE + spriteSeparation, 
          spritePositionY + (PIXELS_PER_ITEM_SPRITE / 2) - (textSize / 2) );
        // Draw the text.
        target.draw( text );
    }
}

bool InventoryGUI::isVisible() { return visible; }

const int InventoryGUI::DEFAULT_BORDER = 10;
const int InventoryGUI::DEFAULT_ITEMS_PER_COL = 8;
const sf::Vector2i InventoryGUI::DEFAULT_ENTRY_SIZE = 
        sf::Vector2i( 128, 19 );
const int InventoryGUI::DEFAULT_SPRITE_SEPARATION = 6;
const int InventoryGUI::DEFAULT_TEXT_SIZE = 12;
const sf::Color InventoryGUI::DEFAULT_BACKGROUND_COLOR = 
        sf::Color( 0, 0, 0, 207 );
const sf::Color InventoryGUI::DEFAULT_TEXT_COLOR = 
        sf::Color( 255, 255, 255, 255 );

sf::RectangleShape *InventoryGUI::makeInventoryBackground() const {
    std::vector<Item *> inventory = Player::getPlayer().getInventory();
    int sizeX = ((( (inventory.size() - 1)/ itemsPerCol )
            + 1 ) * entrySize.x ) + 2 * border;
    int sizeY;

    if( inventory.size() <= itemsPerCol ) {
        sizeY = ( inventory.size() * entrySize.y ) + 2 * border;
    } else {
        sizeY = ( itemsPerCol * entrySize.y ) + 2 * border;
    }

    sf::RectangleShape *background = 
        new sf::RectangleShape( sf::Vector2f( sizeX, sizeY ) );
    background->setFillColor( backgroundColor );
    background->setPosition( -375, -275 );

    return background;
}
