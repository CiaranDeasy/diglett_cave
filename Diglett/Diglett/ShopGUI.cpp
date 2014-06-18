#include "ShopGUI.h"
#include "Player.h"
#include "GameWindow.h"
#include "Constants.h"
#include "Resources.h"

ShopGUI::ShopGUI( Inventory<Item *>& inventory ) : 
        inventory(inventory), 
        background() {
    background.setTexture( 
		    Resources::getResources().getShopBackgroundTexture() );
}

ShopGUI::~ShopGUI(void) {
}

void ShopGUI::draw( 
        sf::RenderTarget& target, 
        sf::RenderStates states ) const {
    sf::Vector2f size = sf::Vector2f( 
            (float) ( 2 * BORDER + COLUMNS * ENTRY_SIZE.x ),
            (float) ( 2 * BORDER + ITEMS_PER_COL * ENTRY_SIZE.y ) );

    sf::Vector2f position = sf::Vector2f(
            ( target.getSize().x / 2 ) - size.x / 2,
            ( target.getSize().y / 2 ) - size.y / 2 );
    std::vector<Item *> contents = inventory.getContents();
    // Draw the inventory background.
    background.setPosition( 
		    sf::Vector2f( position.x, position.y - (float) TOP_BORDER ) );
    target.draw( background );
    for( int i = 0; i < inventory.getCurrentSize(); i++ ) {
        // Calculate the position of the sprite.
        float spritePositionX = 
                position.x + 
				(float) ( BORDER + ( i / ITEMS_PER_COL ) * ENTRY_SIZE.x );
        float spritePositionY =
                position.y + 
				(float) ( BORDER + ( i % ITEMS_PER_COL ) * ENTRY_SIZE.y );
        // Draw the sprite.
        contents[i]->getSprite()->setPosition( 
                spritePositionX, spritePositionY );
        target.draw( *contents[i]->getSprite() );
        // Make the text.
        sf::Text text;
        text.setFont( Resources::getResources().getFont() );
        text.setCharacterSize( TEXT_SIZE );
        text.setColor( TEXT_COLOR );
        text.setString( contents[i]->getName() );
        // Position the text.
        text.setPosition(
          spritePositionX + PIXELS_PER_ITEM_SPRITE + SPRITE_SEPARATION, 
          spritePositionY + (PIXELS_PER_ITEM_SPRITE / 2) - (TEXT_SIZE / 2) );
        // Draw the text.
        target.draw( text );
    }
    // Add the button prompts.
    sf::Text text = sf::Text();
    text.setFont( Resources::getResources().getFont() );
    text.setCharacterSize( TEXT_SIZE );
    text.setColor( TEXT_COLOR );
    if( inventory.getCurrentSize() == 0 ) {
        text.setString( SHORT_BUTTON_PROMPT );
    }
    else {
        text.setString( LONG_BUTTON_PROMPT );
    }
    text.setPosition( position.x + BORDER, 
            position.y + BORDER + ITEMS_PER_COL * ENTRY_SIZE.y );
    target.draw( text );
}

const int ShopGUI::TOP_BORDER = 40;
const int ShopGUI::BORDER = 10;
const int ShopGUI::COLUMNS = 4;
const int ShopGUI::ITEMS_PER_COL = 8;
const sf::Vector2f ShopGUI::ENTRY_SIZE = sf::Vector2f( 128, 19 );
const int ShopGUI::SPRITE_SEPARATION = 6;
const int ShopGUI::TEXT_SIZE = 12;
const sf::Color ShopGUI::TEXT_COLOR = sf::Color( 255, 255, 255, 255 );
const std::string ShopGUI::SHORT_BUTTON_PROMPT = "ESC/Gamepad B: Exit.";
const std::string ShopGUI::LONG_BUTTON_PROMPT = 
        "SPACE/Gamepad A: Sell all.           ESC/Gamepad B: Exit.";
