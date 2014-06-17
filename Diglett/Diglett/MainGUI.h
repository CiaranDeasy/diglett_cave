#pragma once
#include <SFML/Graphics.hpp>
#include "HullGUI.h"
#include "DebugOverlayGUI.h"
#include "InventoryGUI.h"
#include "MoneyGUI.h"
#include "NewItemVisual.h"
#include "Player.h"

/* An instance of this class represents the whole game GUI overlaying the world.
*/

class MainGUI : public sf::Drawable {
public:

    MainGUI( Player& player );
    ~MainGUI();

    // Draws the GUI to the given RenderTarget using the options specified 
    // in the given RenderStates.
    virtual void draw( 
            sf::RenderTarget& target, sf::RenderStates states ) const;

    // Advances the object's state by one game tick.
    void tick();

    void toggleDebugOverlay();
    void toggleInventoryGUI();

private: 

    HullGUI hullGUI;
    DebugOverlayGUI debugOverlay;
    InventoryGUI inventoryGUI;
    MoneyGUI moneyGUI;
    std::vector<NewItemVisual *> newItemVisuals;
    Inventory<Item *>& inventory;

    // Records the last observed inventory size to detect when the player picks
    // up an item.
    int expectedInventorySize;

    // Test whether the player obtained a new Item since the last call, and make
    // a NewItemVisual if they did.
    void triggerNewItemVisual();

    // Ages the NewItemVisuals by one tick, and deletes any that die.
    void processNewItemVisuals();

};

