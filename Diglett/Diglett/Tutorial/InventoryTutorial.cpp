#include "InventoryTutorial.h"
#include "PopUpGameState.h"
#include "Player.h"

InventoryTutorial::InventoryTutorial() {}

InventoryTutorial::~InventoryTutorial() {}

bool InventoryTutorial::testTrigger( World& world ) {
    // Activate this tutorial after the player digs an ore.
   return Player::getPlayer().getInventory().getCurrentSize() != 0;
}

void InventoryTutorial::activate( GameWindow *gameWindow, sf::Font& font ) {
    gameWindow->pushNewState( new PopUpGameState( gameWindow, font, message ) );
    triggered = true;
}

const std::string InventoryTutorial::message = 
        "You dug an ore!\n"
        "Press I or Gamepad \"Y\" to open your inventory.\n"
        "Press U or Gamepad \"X\" to open the shop.\n"
        "Press SPACE or Gamepad \"A\" to continue.";