#include <iostream>
#include <SFML/Graphics.hpp>
#include "Constants.h"
#include "WorldData.h"
#include "Player.h"
#include "Utility.h"
#include "GameWindow.h"

int main() {
    GameWindow::getGameWindow()->mainLoop();
    return 0;
}