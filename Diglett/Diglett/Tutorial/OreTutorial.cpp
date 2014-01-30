#include "OreTutorial.h"
#include "PopUpGameState.h"
#include "WorldData.h"
#include "Player.h"

OreTutorial::OreTutorial() {}

OreTutorial::~OreTutorial() {}

bool OreTutorial::testTrigger() {
    // Activate this tutorial when the player is near an ore.
    // Test all blocks within two tiles.
    WorldData& world = WorldData::getWorldData();
    sf::Vector2f& position = Player::getPlayer().getPosition();
    for( int i = 0; i < 5; i++ ) {
      for( int j = 0; j < 5; j++ ) {
        if( world.getTile( sf::Vector2i( 
                floor( position.x - 2 + i ),
                floor( position.y - 2 + j ) ) ).isOre() ) {
            return true;
        }
      }
    }
    return false;
}

void OreTutorial::activate( GameWindow *gameWindow, sf::Font& font ) {
    gameWindow->pushNewState( new PopUpGameState( gameWindow, font, message ) );
    triggered = true;
}

const std::string OreTutorial::message = 
        "That coloured tile is an ore. Dig it!!!\n"
        "Press SPACE or Gamepad \"A\" to continue.";