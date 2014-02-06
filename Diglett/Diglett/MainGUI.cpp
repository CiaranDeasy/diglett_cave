#include "MainGUI.h"
#include "GameState.h"

MainGUI::MainGUI( sf::Font& font, Inventory<Item *>& inventory ) :
        font( font ),
        hullGUI( font ),
        debugOverlay( font ),
        inventoryGUI( font, inventory ),
        moneyGUI( font ) {
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
    int currentInventorySize = 
            Player::getPlayer().getInventory().getCurrentSize();
    if( currentInventorySize > expectedInventorySize ) {
        Item *item = Player::getPlayer().getInventory().getContents()
                [currentInventorySize - 1];
        newItemVisuals.push_back( new NewItemVisual( font, item ) );
    }
    expectedInventorySize = currentInventorySize;
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
