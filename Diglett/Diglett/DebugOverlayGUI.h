#pragma once
#ifndef DEBUG_OVERLAY_GUI_H
#define DEBUG_OVERLAY_GUI_H

#include <SFML/Graphics.hpp>
#include "Player.h"

/* An instance of this class represents an interface element displaying the 
   player's current hull strength.
*/

class DebugOverlayGUI : public sf::Drawable {
public:

    DebugOverlayGUI( Player& player );
    ~DebugOverlayGUI();

    // Shows or hides the GUI.
    void toggle();

    // Returns true if the GUI is visible in the game window.
    bool isVisible() const;

    // Draws the GUI to the given RenderTarget.
    virtual void draw( sf::RenderTarget& target, sf::RenderStates states ) const;

private: 
    
    // The position of the GUI in the game window. Positive values indicate 
    // offset from the top/left, negative from the bottom/right.
    static const sf::Vector2i GUI_SIZE;
    static const sf::Vector2i POSITION;
    static const int TEXT_SIZE;
    static const sf::Color BACKGROUND_COLOR;
    static const sf::Color TEXT_COLOR;

    // Reference to the player to record their position.
    Player& player;

    // Indicates whether the GUI is visible in the game window.
    bool visible;

};

#endif // DEBUG_OVERLAY_GUI_H
