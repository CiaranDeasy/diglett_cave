#include "MainGUI.h"
#include "GameState.h"

MainGUI::MainGUI( sf::Font& font, Player& player ) :
        font( font ),
        hullGUI( font, player ),
        debugOverlay( font, player ),
        inventoryGUI( font, player.getInventory() ),
        moneyGUI( font, player ),
        inventory( player.getInventory() ) {
    expectedInventorySize = inventory.getCurrentSize();
}

MainGUI::~MainGUI(void) {
}

void MainGUI::draw( sf::RenderTarget& target, sf::RenderStates states ) const {
    target.draw( hullGUI );
    if( debugOverlay.isVisible() ) {
        target.draw( debugOverlay );
    }
    if( inventoryGUI.isVisible() ) {
        target.draw( inventoryGUI );
    }
    target.draw( moneyGUI );

    // Display the NewItemVisuals.
    std::vector<NewItemVisual *>::const_iterator next = newItemVisuals.begin();
    while( next != newItemVisuals.end() ) {
        if( (*next)->isAlive() ) {
            target.draw(**next);
            next++;
        } else next++;
    }
}

void MainGUI::tick() {
    triggerNewItemVisual();
    processNewItemVisuals();
}

void MainGUI::toggleDebugOverlay() {
    debugOverlay.toggle();
}

void MainGUI::toggleInventoryGUI() {
    inventoryGUI.toggle();
}

void MainGUI::triggerNewItemVisual() {
    // Check if the player's inventory grew.
    int currentSize = inventory.getCurrentSize();
    if( currentSize > expectedInventorySize ) {
        Item *item = inventory.getContents()[currentSize - 1];
        newItemVisuals.push_back( new NewItemVisual( font, item ) );
    }
    expectedInventorySize = currentSize;
}

void MainGUI::processNewItemVisuals() {
    std::vector<NewItemVisual *>::iterator next = 
         newItemVisuals.begin();
    while( next != newItemVisuals.end() ) {
        if( (*next)->isAlive() ) {
            (*next)->tick();
            next++;
        } else {
            // Cleanup dead NewItemVisuals.
            delete *next;
            next = newItemVisuals.erase( next );
        }
    }
}
