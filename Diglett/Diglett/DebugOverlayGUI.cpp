#include "DebugOverlayGUI.h"
#include "Resources.h"

DebugOverlayGUI::DebugOverlayGUI( Player& player ) : 
        player( player ) {
    visible = false;
}

DebugOverlayGUI::~DebugOverlayGUI(void) {
}

void DebugOverlayGUI::toggle() {
    visible = !visible;
}

bool DebugOverlayGUI::isVisible() const { return visible; }


void DebugOverlayGUI::draw( 
        sf::RenderTarget& target, 
        sf::RenderStates states ) const {
    // Determine the position vector. Negative values indicate offsets from the
    // right/bottom.
    sf::Vector2i position = POSITION;
    if( position.x < 0 ) position.x = target.getSize().x + position.x;
    if( position.y < 0 ) position.y = target.getSize().y + position.y;
    // Draw the background.
    sf::RectangleShape background = sf::RectangleShape( 
            sf::Vector2f( (float) GUI_SIZE.x, (float) GUI_SIZE.y ) );
    background.setFillColor( BACKGROUND_COLOR );
    background.setPosition( (float) position.x, (float) position.y );
    target.draw( background );
    // Draw the text.
    std::string textString = 
            "Player Position = \n(" + 
            std::to_string( player.getPosition().x ) + "," + 
            std::to_string( player.getPosition().y ) + ")";
    sf::Text text = sf::Text( 
		    textString, Resources::getResources().getFont(), TEXT_SIZE );
    text.setPosition( (float) ( position.x + 5 ), (float) ( position.y + 5 ) );
    text.setColor( TEXT_COLOR ); 
    target.draw( text );
}

const sf::Vector2i DebugOverlayGUI::GUI_SIZE = sf::Vector2i( 130, 100 );
const sf::Vector2i DebugOverlayGUI::POSITION = 
        sf::Vector2i( 0, -GUI_SIZE.y );
const int DebugOverlayGUI::TEXT_SIZE = 12;
const sf::Color DebugOverlayGUI::BACKGROUND_COLOR = sf::Color( 0, 0, 0, 207 );
const sf::Color DebugOverlayGUI::TEXT_COLOR = 
        sf::Color( 255, 255, 255, 255 );