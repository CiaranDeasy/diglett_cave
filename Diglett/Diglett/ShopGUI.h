#pragma once
#ifndef SHOP_GUI_H
#define SHOP_GUI_H

#include <SFML/Graphics.hpp>
#include "Inventory.h"
#include "Item.h"

/* This class represents the GUI display when the player is in the ore-selling 
   shop. */

class ShopGUI : public sf::Drawable {
public:

    ShopGUI( Inventory<Item *>& inventory );
    ~ShopGUI();

    // Draws the inventory GUI to the given RenderTarget using the options
    // specified in the given RenderStates.
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private: 
    static const int TOP_BORDER;
    static const int BORDER;
    static const int COLUMNS;
    static const int ITEMS_PER_COL;
    static const sf::Vector2f ENTRY_SIZE;
    static const int SPRITE_SEPARATION;
    static const int TEXT_SIZE;
    static const sf::Color BACKGROUND_COLOR;
    static const sf::Color TEXT_COLOR;
    static const std::string SHORT_BUTTON_PROMPT;
    static const std::string LONG_BUTTON_PROMPT;

    // The player inventory to be displayed.
    Inventory<Item *>& inventory;

    mutable sf::Sprite background;

};

#endif // SHOP_GUI_H
