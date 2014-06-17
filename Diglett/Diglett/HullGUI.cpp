#include "HullGUI.h"
#include "Constants.h"
#include "Resources.h"

HullGUI::HullGUI( Player& player ) : 
        player( player ) {
}

HullGUI::~HullGUI(void) {
}

void HullGUI::draw( 
        sf::RenderTarget& target, 
        sf::RenderStates states ) const {
    // Determine the position vector. Negative values indicate offsets from the
    // right/bottom.
    sf::Vector2i position = POSITION;
    if( position.x < 0 ) position.x = target.getSize().x + position.x;
    if( position.y < 0 ) position.y = target.getSize().y + position.y;
    // Draw the background.
    sf::RectangleShape background = sf::RectangleShape( 
            sf::Vector2f( GUI_SIZE.x, GUI_SIZE.y ) );
    background.setFillColor( BACKGROUND_COLOR );
    background.setPosition( position.x, position.y );
    target.draw( background );
    // Fill according to current hull strength.
    float currentHullFraction = (float) player.getCurrentHull() / 
            (float) player.getMaxHull();
    sf::RectangleShape fill = sf::RectangleShape( 
            sf::Vector2f( 
                currentHullFraction * ( GUI_SIZE.x - 2*BORDER_THICKNESS ), 
                ( GUI_SIZE.y - 2*BORDER_THICKNESS ) ) );
    fill.setFillColor( FILL_COLOR );
    fill.setPosition( position.x + BORDER_THICKNESS, 
            position.y + BORDER_THICKNESS );
    target.draw( fill );
    // Draw the text.
    std::string textString = 
            std::to_string( player.getCurrentHull() ) + "/" + 
            std::to_string( player.getMaxHull() );
    sf::Text text = sf::Text( 
		    textString, Resources::getResources().getFont(), TEXT_SIZE );
    text.setStyle( sf::Text::Bold );
    text.setOrigin( text.getLocalBounds().width / 2, 
            text.getLocalBounds().height / 2 );
    text.setPosition( position.x + (GUI_SIZE.x/2), 
            position.y + (GUI_SIZE.y/2) );
    target.draw( text );
}

const sf::Vector2i HullGUI::GUI_SIZE = sf::Vector2i( 100, 20 );
const sf::Vector2i HullGUI::POSITION = 
        sf::Vector2i( -10 - GUI_SIZE.x, 10 );
const int HullGUI::TEXT_SIZE = 12;
const sf::Color HullGUI::BACKGROUND_COLOR = sf::Color( 0, 0, 0, 255 );
const sf::Color HullGUI::FILL_COLOR = sf::Color( 255, 0, 0, 255 );
const sf::Color HullGUI::TEXT_COLOR = 
        sf::Color( 255, 255, 255, 255 );
const int HullGUI::BORDER_THICKNESS = 2;