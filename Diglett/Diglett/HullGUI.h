#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

/* An instance of this class represents an interface element displaying the 
   player's current hull strength.
*/

class HullGUI : public sf::Drawable {
public:

    HullGUI( sf::Font& font, Player& player );
    ~HullGUI();

    // Draws the GUI to the given RenderTarget using the options specified 
    // in the given RenderStates.
    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

private: 
    
    // The position of the GUI in the game window. Positive values indicate 
    // offset from the top/left, negative from the bottom/right.
    static const sf::Vector2i GUI_SIZE;
    static const sf::Vector2i POSITION;
    static const int TEXT_SIZE;
    static const sf::Color BACKGROUND_COLOR;
    static const sf::Color FILL_COLOR;
    static const sf::Color TEXT_COLOR;
    static const int BORDER_THICKNESS;

    sf::Font& font;
    Player& player;

};

