#include "OpenShopTutorial.h"
#include "PopUpGameState.h"
#include "Player.h"

OpenShopTutorial::OpenShopTutorial() {}

OpenShopTutorial::~OpenShopTutorial() {}

bool OpenShopTutorial::testTrigger( World& world, Player& player ) {
    // Activate this tutorial when the player is near the shop.
    sf::Vector2f& playerPos = player.getPosition();
	const sf::Vector2f& shopPos = world.getShopPosition();
	return ( abs( shopPos.x - playerPos.x ) < 1 ) 
		    && ( abs( shopPos.y - playerPos.y ) < 1 );
}

void OpenShopTutorial::activate( GameWindow *gameWindow ) {
    gameWindow->pushNewState( new PopUpGameState( gameWindow, message ) );
    triggered = true;
}

const std::string OpenShopTutorial::message = 
        "Press SPACE or Gamepad A to open the shop.\n"
		"The shop is where you come to sell your ores for money.";
