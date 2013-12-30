#include "Player.h"
#include <iostream>
#include "Tile.h"
#include "WorldData.h"
#include "InputHandler.h"
#include "Physics.h"

#define TAN30 0.57735
#define TAN60 1.73205

Player& Player::getPlayer() {
    return singleton;
}

sf::Vector2f Player::getPosition() {
    return position;
}

void Player::move( float x, float y ) {
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
    // Classify movement direction.
    Direction directionOfMovement = classifyDirectionOfMovement(x, y);
    // Check for collisions.
    float oldX = position.x;
    float oldY = position.y;
    float newX = oldX + x;
    float newY = oldY + y;
    // Check for clipping with tiles to the left.
    if( directionOfMovement > 8 && directionOfMovement < 16 &&
            floor( oldX + leftClip ) > floor( newX + leftClip ) ) {
        sf::Vector2i topTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + leftClip, oldY + topClip ) );
        sf::Vector2i bottomTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + leftClip, oldY + bottomClip ) );
        Tile& topTile = WorldData::getWorldData().getTile( topTileCoords );
        Tile& bottomTile = WorldData::getWorldData().getTile(bottomTileCoords);
        // Test if the player is trying to dig.
        if( InputHandler::getDirectionOfMovement() >= 11 && 
                InputHandler::getDirectionOfMovement() <= 13 &&
                onGround == DIG_DELAY  && topTile.isDiggable() ) {
            initiateDigging( topTileCoords );
        }
        if( topTile.isSolid() || bottomTile.isSolid() ) {
            newX = floor( oldX ) - leftClip + 0.001;
            Physics::getPhysics().collideX();
        }
    }
    // Check for clipping with tiles to the right.
    if( directionOfMovement > 0 && directionOfMovement < 8 &&
            floor( oldX + rightClip ) < floor( newX + rightClip ) ) {
        sf::Vector2i topTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + rightClip, oldY + topClip ) );
        sf::Vector2i bottomTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + rightClip, oldY + bottomClip ) );
        Tile& topTile = WorldData::getWorldData().getTile( topTileCoords );
        Tile& bottomTile = WorldData::getWorldData().getTile(bottomTileCoords);
        // Test if the player is trying to dig.
        if( InputHandler::getDirectionOfMovement() >= 3 && 
                InputHandler::getDirectionOfMovement() <= 5 &&
                onGround == DIG_DELAY && topTile.isDiggable()) {
            initiateDigging( topTileCoords );
        }
        if( topTile.isSolid() || bottomTile.isSolid() ) {
            newX = floor( oldX + 1 ) - 0.001 - rightClip;
            Physics::getPhysics().collideX();
        }
    }
    // Check for clipping with tiles above.
    if( ( directionOfMovement < 4 || directionOfMovement > 12 ) &&
            floor( oldY + topClip ) < floor( newY + topClip ) ) {
        sf::Vector2i leftTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + leftClip, newY + topClip ) );
        sf::Vector2i rightTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + rightClip, newY + topClip ) );
        Tile& leftTile = WorldData::getWorldData().getTile( leftTileCoords );
        Tile& rightTile = WorldData::getWorldData().getTile( rightTileCoords );
        if( leftTile.isSolid() || rightTile.isSolid() ) {
            newY = floor( oldY + 1 ) - 0.001 - topClip;
            Physics::getPhysics().collideY();
        }
    }
    // Check for clipping with tiles below.
    if( directionOfMovement > 4 && directionOfMovement < 12 &&
            floor( oldY + bottomClip ) > floor( newY + bottomClip ) ) {
        sf::Vector2i leftTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + leftClip, newY + bottomClip ) );
        sf::Vector2i rightTileCoords = Utility::coordsGameToTile(
                sf::Vector2f( newX + rightClip, newY + bottomClip ) );
        Tile& leftTile = WorldData::getWorldData().getTile( leftTileCoords );
        Tile& rightTile = WorldData::getWorldData().getTile( rightTileCoords );
        // Test if the player is trying to dig.
        if( InputHandler::getDirectionOfMovement() >= 7 && 
                InputHandler::getDirectionOfMovement() <= 9 &&
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
            newY = floor( oldY ) - bottomClip + 0.001;
            Physics::getPhysics().collideY();
            if( onGround < DIG_DELAY ) onGround++;
        } else onGround = 0;
    } else onGround = 0;
    if( digging ) processDiggingStep();
    else position = sf::Vector2f( newX, newY );
}

bool Player::addMoney( int amount ) {
    if( -amount > money ) return false;
    money += amount;
    return true;
}

Player Player::singleton = Player();

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

Player::Player(void) {
    position = sf::Vector2f( 1.0f, 1.0f );
    topClip = 0.45;
    bottomClip = -0.45;
    leftClip = -0.45;
    rightClip = 0.45;
    money = DEFAULT_MONEY;
}

Player::~Player(void) {
}

Player::Direction Player::classifyDirectionOfMovement(
        float deltaX, float deltaY ) {

    // Handle the X=0 case.
    if( deltaX == 0 ) {
        if( deltaY < 0 ) {
            return South;
        } else return North;
    }

    float tan = deltaY/deltaX;
    // Take absolute value.
    tan = (tan >= 0) ? tan : (0 - tan);
    if( deltaX > 0 ) {
        if( deltaY <= 0 ) {
            // South-east quadrant.
            if( tan < TAN30 ) return Eastsoutheast;
            else if( tan > TAN60 ) return Southsoutheast;
            else return Southeast;
        } else {
            // North-east quadrant.
            if( tan < TAN30 ) return Eastnortheast;
            else if( tan > TAN60 ) return Northnortheast;
            else return Northeast;
        }
    } else {
        if( deltaY <= 0 ) {
            // South-west quadrant.
            if( tan < TAN30 ) return Westsouthwest;
            else if( tan > TAN60 ) return Southsouthwest;
            else return Southwest;
        } else {
            // North-west quadrant.
            if( tan < TAN30 ) return Westnorthwest;
            else if( tan > TAN60 ) return Northnorthwest;
            else return Northwest;
        }
    }
}