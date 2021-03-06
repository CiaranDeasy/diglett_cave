#pragma once
#ifndef MONEY_GUI_H
#define MONEY_GUI_H

#include <SFML/Graphics.hpp>
#include "Player.h"

/* An instance of this class represents an interface element displaying the 
   player's current money.
*/

class MoneyGUI : public sf::Drawable {
public:

    MoneyGUI( Player& player );
    ~MoneyGUI();

    // Draws the GUI to the given RenderTarget.
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private: 
    
    static const sf::Vector2i GUI_SIZE;
    static const int DISPLACEMENT_FROM_TOP;
    static const int TEXT_SIZE;
    static const sf::Color BACKGROUND_COLOR;
    static const sf::Color TEXT_COLOR;

    Player& player;

};

#endif // MONEY_GUI_H