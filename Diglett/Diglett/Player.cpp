#include "Player.h"
#include <iostream>
#include "WorldData.h"
#include "Physics.h"
#include "Constants.h"

#define TAN30 0.57735
#define TAN60 1.73205

Player& Player::getPlayer() {
    return singleton;
}

Player::~Player(void) {
}

sf::Vector2f Player::getPosition() {
    return position;
}

void Player::move( float x, float y, Direction directionOfInput ) {
    // The program will crash if attempting to load a chunk outside the world.
    // Constrain movement until infinite worlds are implemented.
    if( position.x + x > 150 || position.x + x < -150 ) {
        Physics::getPhysics().collideX();
        return;
    }
    if( position.y + y > 150 || position.y + y < -150 ) {
        Physics::getPhysics().collideY();
        return;
    }

    // If player is currently digging, disregard input and process dig step.
    if( digging ) {
        processDiggingStep();
        return;
    }

    // Check for collisions.
    float oldX = position.x;
    float oldY = position.y;
    float newX = oldX + x;
    float newY = oldY + y;

    if( clipLeft( oldX, oldY, newX, newY, directionOfInput ) ) {
            newX = floor( oldX ) - leftClip + 0.001;
            Physics::getPhysics().collideX();
    } else if( clipRight( oldX, oldY, newX, newY, directionOfInput ) ) {
        newX = floor( oldX + 1 ) - 0.001 - rightClip;
        Physics::getPhysics().collideX();
    }
    if( clipAbove( oldX, oldY, newX, newY, directionOfInput ) ) {
        newY = floor( oldY + 1 ) - 0.001 - topClip;
        Physics::getPhysics().collideY();
    } else if( clipBelow( oldX, oldY, newX, newY, directionOfInput ) ) {
        newY = floor( oldY ) - bottomClip + 0.001;
        Physics::getPhysics().collideY();
        if( onGround < DIG_DELAY ) onGround++;
    }

    if( digging ) processDiggingStep();
    else position = sf::Vector2f( newX, newY );
}

Inventory<Item *>& Player::getInventory() { return inventory; }

bool Player::addMoney( int amount ) {
    if( -amount > money ) return false;
    money += amount;
    return true;
}

int Player::getMaxHull() { return maxHull; }
int Player::getCurrentHull() { return currentHull; }

void Player::damageHull( int damage ) {
    currentHull -= damage;
    if( currentHull < 0 ) currentHull = 0;
}

bool Player::isDead() {
    return currentHull == 0;
}

void Player::respawn() {
    currentHull = maxHull;
    std::vector<Item *> contents = inventory.getContents();
    std::vector<Item *>::iterator next = contents.begin();
    while( next != contents.end() ) {
        delete *next;
        next++;
    }
    inventory.clear();
}

Player Player::singleton = Player();

Player::Player(void) {
    position = sf::Vector2f( 1.0f, 1.0f );
    topClip = 0.45;
    bottomClip = -0.45;
    leftClip = -0.45;
    rightClip = 0.45;
    money = DEFAULT_MONEY;
    maxHull = DEFAULT_HULL;
    currentHull = DEFAULT_HULL;
}

void Player::initiateDigging( sf::Vector2i target ) {
    digging = true;
    // Calculate the step size in the X direction.
    float distanceToTravelX = ( target.x + 0.5 ) - position.x;
    float diggingStepSizeX = distanceToTravelX / DIG_STEPS;
    // Calculate the step size in the Y direction.
    float distanceToTravelY = ( target.y - bottomClip + 0.001 ) - position.y;
    float diggingStepSizeY = distanceToTravelY / DIG_STEPS;
    // Combine them.
    diggingStepSize = sf::Vector2f(diggingStepSizeX, diggingStepSizeY);
    diggingStepsRemaining = DIG_STEPS;
    diggingTowards = target;
}

void Player::processDiggingStep() {
    position += diggingStepSize;
    diggingStepsRemaining--;
    if (diggingStepsRemaining == 0) {
        digging = false;
        Physics::getPhysics().reset();
        // Dig the tile.
        WorldData::getWorldData().getTile( diggingTowards ).dig();
    }
}

bool Player::clipLeft( float oldX, float oldY, float newX, float newY,
        Direction directionOfInput ) {
    if( floor( oldX + leftClip ) > floor( newX + leftClip ) ) {
        sf::Vector2i topTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + leftClip, oldY + topClip ) );
        sf::Vector2i bottomTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + leftClip, oldY + bottomClip ) );
        Tile& topTile = WorldData::getWorldData().getTile( topTileCoords );
        Tile& bottomTile = WorldData::getWorldData().getTile(bottomTileCoords);
        // Test if the player is trying to dig.
        if( directionOfInput >= 11 && directionOfInput <= 13 && 
                onGround == DIG_DELAY && topTile.isDiggable() ) {
            initiateDigging( topTileCoords );
        }
        if( topTile.isSolid() || bottomTile.isSolid() ) {
            return true;
        }
    }
    return false;
}

bool Player::clipRight( float oldX, float oldY, float newX, float newY,
        Direction directionOfInput ) {
    if( floor( oldX + rightClip ) < floor( newX + rightClip ) ) {
        sf::Vector2i topTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + rightClip, oldY + topClip ) );
        sf::Vector2i bottomTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + rightClip, oldY + bottomClip ) );
        Tile& topTile = WorldData::getWorldData().getTile( topTileCoords );
        Tile& bottomTile = WorldData::getWorldData().getTile(bottomTileCoords);
        // Test if the player is trying to dig.
        if( directionOfInput >= 3 && directionOfInput <= 5 &&
                onGround == DIG_DELAY && topTile.isDiggable()) {
            initiateDigging( topTileCoords );
        }
        if( topTile.isSolid() || bottomTile.isSolid() ) {
            return true;
        }
    }
    return false;
}

bool Player::clipAbove( float oldX, float oldY, float newX, float newY,
        Direction directionOfInput ) {
    if( floor( oldY + topClip ) < floor( newY + topClip ) ) {
        sf::Vector2i leftTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + leftClip, newY + topClip ) );
        sf::Vector2i rightTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + rightClip, newY + topClip ) );
        Tile& leftTile = WorldData::getWorldData().getTile( leftTileCoords );
        Tile& rightTile = WorldData::getWorldData().getTile( rightTileCoords );
        if( leftTile.isSolid() || rightTile.isSolid() ) {
            return true;
        }
    }
    return false;
}

bool Player::clipBelow( float oldX, float oldY, float newX, float newY,
        Direction directionOfInput ) {
    if( floor( oldY + bottomClip ) > floor( newY + bottomClip ) ) {
        sf::Vector2i leftTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + leftClip, newY + bottomClip ) );
        sf::Vector2i rightTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + rightClip, newY + bottomClip ) );
        Tile& leftTile = WorldData::getWorldData().getTile( leftTileCoords );
        Tile& rightTile = WorldData::getWorldData().getTile( rightTileCoords );
        // Test if the player is trying to dig.
        if( directionOfInput >= 7 && directionOfInput <= 9 &&
                onGround == DIG_DELAY ) {
            float offSet = oldX - floor( oldX );
            // Dig the tile that the player is more over, or neither if they 
            // are too close to the middle.
            if( offSet > 0.2 && offSet <= 0.5 && rightTile.isDiggable() ) {
                initiateDigging(rightTileCoords);
            } else if( offSet > 0.5 && offSet <= 0.8 && leftTile.isDiggable() ) {
                initiateDigging(leftTileCoords);
            }
        }
        // Do the actual clipping.
        if( leftTile.isSolid() || rightTile.isSolid() ) {
            return true;
        } else onGround = 0;
    } else onGround = 0;
    return false;
}
