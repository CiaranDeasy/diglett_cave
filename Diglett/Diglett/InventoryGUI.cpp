#include "InventoryGUI.h"
#include "Player.h"
#include "GameWindow.h"

void InventoryGUI::triggerInventoryGUI() {
    visible = true;
    expectedInventorySize = Player::getPlayer().getInventory().size();
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
            -(WINDOW_RESOLUTION.x /2) + INVENTORY_POSITION.x + INVENTORY_BORDER
                + ( i / INVENTORY_ITEMS_PER_COL ) * INVENTORY_ENTRY_SIZE.x;
        int spritePositionY =
            -(WINDOW_RESOLUTION.y /2) + INVENTORY_POSITION.y + INVENTORY_BORDER
                + ( i % INVENTORY_ITEMS_PER_COL ) * INVENTORY_ENTRY_SIZE.y;
        // Draw the sprite.
        inventory[i]->getSprite()->setPosition( 
                spritePositionX, spritePositionY );
        target.draw( *inventory[i]->getSprite() );
        // Make the text.
        sf::Text text;
        // TODO: make the font internal to InventoryGUI.
        text.setFont( GameWindow::getGameWindow()->getFont() );
        text.setCharacterSize( INVENTORY_TEXT_SIZE );
        text.setColor( sf::Color:: White );
        text.setString( inventory[i]->getName() );
        // Position the text.
        text.setPosition(
          spritePositionX + PIXELS_PER_ITEM_SPRITE + 
            INVENTORY_SPRITE_SEPARATION, 
          spritePositionY + (PIXELS_PER_ITEM_SPRITE / 2) - 
            (INVENTORY_TEXT_SIZE / 2) );
        // Draw the text.
        target.draw( text );
    }
}

void InventoryGUI::clearInventoryGUI() {
    visible = false;
}

void InventoryGUI::toggleInventoryGUI() {
    if( visible ) clearInventoryGUI();
    else triggerInventoryGUI();
}

sf::RectangleShape *InventoryGUI::makeInventoryBackground() {
    std::vector<Item *> inventory = Player::getPlayer().getInventory();
    int sizeX = ((( (inventory.size() - 1)/ INVENTORY_ITEMS_PER_COL )
            + 1 ) * INVENTORY_ENTRY_SIZE.x ) + 2 * INVENTORY_BORDER;
    int sizeY;

    if( inventory.size() <= INVENTORY_ITEMS_PER_COL ) {
        sizeY = ( inventory.size() * INVENTORY_ENTRY_SIZE.y ) + 
                2 * INVENTORY_BORDER;
    } else {
        sizeY = ( INVENTORY_ITEMS_PER_COL * INVENTORY_ENTRY_SIZE.y ) + 
                2 * INVENTORY_BORDER;
    }

    sf::RectangleShape *background = 
        new sf::RectangleShape( sf::Vector2f( sizeX, sizeY ) );
    background->setFillColor( sf::Color( 0, 0, 0, 207 ) );
    background->setPosition( -375, -275 );

    return background;
}

bool InventoryGUI::isVisible() { return visible; }

InventoryGUI::InventoryGUI(void) {
    visible = false;
}

InventoryGUI::~InventoryGUI(void) {
}
