#include "InventoryTutorial.h"
#include "PopUpGameState.h"
#include "Player.h"

InventoryTutorial::InventoryTutorial() {}

InventoryTutorial::~InventoryTutorial() {}

bool InventoryTutorial::testTrigger( World& world, Player& player ) {
    // Activate this tutorial after the player digs an ore.
   return player.getInventory().getCurrentSize() != 0;
}

void InventoryTutorial::activate( GameWindow *gameWindow ) {
    gameWindow->pushNewState( new PopUpGameState( gameWindow, message ) );
    triggered = true;
}

const std::string InventoryTutorial::message = 
        "You dug an ore!\n"
        "Press I or Gamepad \"Y\" to open your inventory.\n"
        "Visit the shop to sell your ore.\n"
        "Press SPACE or Gamepad \"A\" to continue.";
