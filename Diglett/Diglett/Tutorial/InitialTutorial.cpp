#include "InitialTutorial.h"
#include "PopUpGameState.h"

InitialTutorial::InitialTutorial() {}

InitialTutorial::~InitialTutorial() {}

bool InitialTutorial::testTrigger( World& world, Player& player ) {
    // Activate this tutorial when the game starts.
    return true;
}

void InitialTutorial::activate( GameWindow *gameWindow, sf::Font& font ) {
    gameWindow->pushNewState( new PopUpGameState( gameWindow, font, message ) );
    triggered = true;
}

const std::string InitialTutorial::message = 
        "Welcome to Project Diglett!\n"
        "Use the WASD keys or Gamepad left stick to move.\n"
        "Move into a dirt block to dig it.\n"
        "Dig down to find some gold!\n"
        "Press SPACE or Gamepad \"A\" to begin.";