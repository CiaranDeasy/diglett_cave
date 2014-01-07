#include "Gamestate.h"

GameState::GameState() {
    dead = false;
}

GameState::~GameState() {
}

bool GameState::isDead() { return dead; }