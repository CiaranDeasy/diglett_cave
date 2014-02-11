#pragma once
#include <SFML/Graphics.hpp>
#include "Inventory.h"
#include "Item.h"

/* This class represents the GUI display when the player is in the ore-selling 
   shop. */

class ShopGUI : public sf::Drawable {
public:

    ShopGUI( sf::Font& font, Inventory<Item *>& inventory );
    ~ShopGUI();

    // Draws the inventory GUI to the given RenderTarget using the options
    // specified in the given RenderStates.
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private: 
    static const int BORDER;
    static const int COLUMNS;
    static const int ITEMS_PER_COL;
    static const sf::Vector2i ENTRY_SIZE;
    static const int SPRITE_SEPARATION;
    static const int TEXT_SIZE;
    static const sf::Color BACKGROUND_COLOR;
    static const sf::Color TEXT_COLOR;

    // The player inventory to be displayed.
    Inventory<Item *>& inventory;

    sf::Font& font;

};
