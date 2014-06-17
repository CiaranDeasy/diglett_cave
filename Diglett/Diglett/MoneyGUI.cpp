#include "MoneyGUI.h"
#include "Resources.h"

MoneyGUI::MoneyGUI( Player& player ) : 
        player( player ) {
}

MoneyGUI::~MoneyGUI(void) {
}

void MoneyGUI::draw( 
        sf::RenderTarget& target, 
        sf::RenderStates states ) const {
    // Determine the position vector.
    sf::Vector2i position = 
            sf::Vector2i( target.getSize().x / 2, DISPLACEMENT_FROM_TOP );
    // Draw the background.
    sf::RectangleShape background = sf::RectangleShape( 
            sf::Vector2f( GUI_SIZE.x, GUI_SIZE.y ) );
    background.setFillColor( BACKGROUND_COLOR );
    background.setOrigin( GUI_SIZE.x / 2, 0 );
    background.setPosition( position.x, position.y );
    target.draw( background );
    // Draw the text.
    std::string textString = "£" + std::to_string( player.getMoney() );
    sf::Text text = sf::Text( 
		    textString, Resources::getResources().getFont(), TEXT_SIZE );
    text.setStyle( sf::Text::Bold );
    sf::FloatRect bounds = text.getLocalBounds();
    text.setOrigin( bounds.left + bounds.width / 2, 
            bounds.top + bounds.height / 2 );
    text.setPosition( position.x, 
            position.y + (GUI_SIZE.y/2) );
    target.draw( text );
}

const sf::Vector2i MoneyGUI::GUI_SIZE = sf::Vector2i( 100, 20 );
const int MoneyGUI::DISPLACEMENT_FROM_TOP = 10;
const int MoneyGUI::TEXT_SIZE = 12;
const sf::Color MoneyGUI::BACKGROUND_COLOR = sf::Color( 0, 0, 0, 207 );
const sf::Color MoneyGUI::TEXT_COLOR = sf::Color( 255, 255, 255, 255 );
