#include "OreTutorial.h"
#include "PopUpGameState.h"
#include "WorldData.h"
#include "Player.h"

OreTutorial::OreTutorial() {}

OreTutorial::~OreTutorial() {}

bool OreTutorial::testTrigger( World& world, Player& player ) {
    // Activate this tutorial when the player is near an ore.
    // Test all blocks within two tiles.
    sf::Vector2f& position = player.getPosition();
    for( int i = 0; i < 5; i++ ) {
      for( int j = 0; j < 5; j++ ) {
        if( world.getTile( (int) floor( position.x - 2 + i ),
               (int) floor( position.y - 2 + j ) ).isOre() ) {
            return true;
        }
      }
    }
    return false;
}

void OreTutorial::activate( GameWindow *gameWindow ) {
    gameWindow->pushNewState( new PopUpGameState( gameWindow, message ) );
    triggered = true;
}

const std::string OreTutorial::message = 
        "That coloured tile is an ore. Dig it!!!\n"
        "Press SPACE or Gamepad \"A\" to continue.";