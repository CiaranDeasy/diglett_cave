#include "Player.h"
#include <iostream>
#include "WorldData.h"
#include "Physics.h"
#include "Constants.h"
#include "World.h"

#define TAN30 0.57735
#define TAN60 1.73205

Player::~Player(void) {
}

sf::Vector2f Player::getPosition() const {
    return position;
}

void Player::move( float x, float y, Direction directionOfInput, World& world ) {
    // The program will crash if attempting to load a chunk outside the world.
    // Constrain movement until infinite worlds are implemented.
    if( position.x + x > 150 || position.x + x < -150 ) {
        Physics::getPhysics().collideX( *this );
        return;
    }
    if( position.y + y > 150 || position.y + y < -150 ) {
        Physics::getPhysics().collideY( *this );
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

    if( clipLeft( oldX, oldY, newX, newY, directionOfInput, world ) ) {
            newX = floor( oldX ) - leftClip + 0.001f;
            Physics::getPhysics().collideX( *this );
    } else if( clipRight( oldX, oldY, newX, newY, directionOfInput, world ) ) {
        newX = floor( oldX + 1 ) - 0.001f - rightClip;
        Physics::getPhysics().collideX( *this );
    }
    if( clipAbove( oldX, oldY, newX, newY, directionOfInput, world ) ) {
        newY = floor( oldY + 1 ) - 0.001f - topClip;
        Physics::getPhysics().collideY( *this );
    } else if( clipBelow( oldX, oldY, newX, newY, directionOfInput, world ) ) {
        newY = floor( oldY ) - bottomClip + 0.001f;
        Physics::getPhysics().collideY( *this );
        if( onGround < DIG_DELAY ) onGround++;
    }

    if( digging ) {
        processDiggingStep();
    }
    else {
        position = sf::Vector2f( newX, newY );
    }
}

Inventory<Item *>& Player::getInventory() { return inventory; }

int Player::getMoney() { return money; }

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

bool Player::isDead() const {
    return currentHull == 0;
}

void Player::respawn() {
    // Reset the hull.
    currentHull = maxHull;
    // Empty the inventory, deleting each item.
    std::vector<Item *> contents = inventory.getContents();
    std::vector<Item *>::iterator next = contents.begin();
    while( next != contents.end() ) {
        delete *next;
        next++;
    }
    inventory.clear();
    // Reset the player's position.
    position = sf::Vector2f( 1, 1 );
}

Player::Player(void) {
    position = sf::Vector2f( 1.0f, 1.0f );
    topClip = 0.45f;
    bottomClip = -0.45f;
    leftClip = -0.45f;
    rightClip = 0.45f;
    money = DEFAULT_MONEY;
    maxHull = DEFAULT_HULL;
    currentHull = DEFAULT_HULL;
    digging = false;
}

void Player::initiateDigging( sf::Vector2i target, World& world ) {
    digging = true;
    // Calculate the step size in the X direction.
    float distanceToTravelX = ( target.x + 0.5f ) - position.x;
    float diggingStepSizeX = distanceToTravelX / DIG_STEPS;
    // Calculate the step size in the Y direction.
    float distanceToTravelY = ( target.y - bottomClip + 0.001f ) - position.y;
    float diggingStepSizeY = distanceToTravelY / DIG_STEPS;
    // Combine them.
    diggingStepSize = sf::Vector2f(diggingStepSizeX, diggingStepSizeY);
    diggingStepsRemaining = DIG_STEPS;
    diggingTowards = target;
    worldToDig = &world;
}

void Player::processDiggingStep() {
    position += diggingStepSize;
    diggingStepsRemaining--;
    if (diggingStepsRemaining == 0) {
        digging = false;
        Physics::getPhysics().reset();
        // Dig the tile.
        worldToDig->digTile( diggingTowards, *this );
    }
}

bool Player::clipLeft( float oldX, float oldY, float newX, float newY,
        Direction directionOfInput, World& world ) {
    if( floor( oldX + leftClip ) > floor( newX + leftClip ) ) {
        sf::Vector2i topTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + leftClip, oldY + topClip ) );
        sf::Vector2i bottomTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + leftClip, oldY + bottomClip ) );
        const Tile& topTile = world.getTile( topTileCoords );
        const Tile& bottomTile = world.getTile(bottomTileCoords);
        // Test if the player is trying to dig.
        if( directionOfInput >= Westsouthwest && 
                directionOfInput <= Westnorthwest && 
                onGround == DIG_DELAY && topTile.isDiggable() ) {
            initiateDigging( topTileCoords, world );
        }
        if( topTile.isSolid() || bottomTile.isSolid() ) {
            return true;
        }
    }
    return false;
}

bool Player::clipRight( float oldX, float oldY, float newX, float newY,
        Direction directionOfInput, World& world ) {
    if( floor( oldX + rightClip ) < floor( newX + rightClip ) ) {
        sf::Vector2i topTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + rightClip, oldY + topClip ) );
        sf::Vector2i bottomTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + rightClip, oldY + bottomClip ) );
        const Tile& topTile = world.getTile( topTileCoords );
        const Tile& bottomTile = world.getTile(bottomTileCoords);
        // Test if the player is trying to dig.
        if( directionOfInput >= Eastnortheast && 
                directionOfInput <= Eastsoutheast &&
                onGround == DIG_DELAY && topTile.isDiggable()) {
            initiateDigging( topTileCoords, world );
        }
        if( topTile.isSolid() || bottomTile.isSolid() ) {
            return true;
        }
    }
    return false;
}

bool Player::clipAbove( float oldX, float oldY, float newX, float newY,
        Direction directionOfInput, World& world ) {
    if( floor( oldY + topClip ) < floor( newY + topClip ) ) {
        sf::Vector2i leftTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + leftClip, newY + topClip ) );
        sf::Vector2i rightTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + rightClip, newY + topClip ) );
        const Tile& leftTile = world.getTile( leftTileCoords );
        const Tile& rightTile = world.getTile( rightTileCoords );
        if( leftTile.isSolid() || rightTile.isSolid() ) {
            return true;
        }
    }
    return false;
}

bool Player::clipBelow( float oldX, float oldY, float newX, float newY,
        Direction directionOfInput, World& world ) {
    if( floor( oldY + bottomClip ) > floor( newY + bottomClip ) ) {
        sf::Vector2i leftTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + leftClip, newY + bottomClip ) );
        sf::Vector2i rightTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + rightClip, newY + bottomClip ) );
        const Tile& leftTile = world.getTile( leftTileCoords );
        const Tile& rightTile = world.getTile( rightTileCoords );
        // Test if the player is trying to dig.
        if( directionOfInput >= Southsoutheast && 
                directionOfInput <= Southsouthwest &&
                onGround == DIG_DELAY ) {
            float offSet = oldX - floor( oldX );
            // Dig the tile that the player is more over, or neither if they 
            // are too close to the middle.
            if( offSet > 0.2 && offSet <= 0.5 && rightTile.isDiggable() ) {
                initiateDigging( rightTileCoords, world );
            } else if( offSet > 0.5 && offSet <= 0.8 && leftTile.isDiggable() ) {
                initiateDigging( leftTileCoords, world );
            }
        }
        // Do the actual clipping.
        if( leftTile.isSolid() || rightTile.isSolid() ) {
            return true;
        } else onGround = 0;
    } else onGround = 0;
    return false;
}
