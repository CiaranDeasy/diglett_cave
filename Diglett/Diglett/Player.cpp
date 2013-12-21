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
        Tile topTile = WorldData::getWorldData().getTile( 
            floor( newX + leftClip ), floor( oldY + topClip ) );
        Tile bottomTile = WorldData::getWorldData().getTile( 
            floor( newX + leftClip ), floor( oldY + bottomClip ) );
        if( ( topTile.getType() != Tile::Air && 
            topTile.getType() != Tile::Surface ) 
            || ( bottomTile.getType() != Tile::Air && 
            bottomTile.getType() != Tile::Surface ) ) {
            newX = floor( oldX ) - leftClip + 0.001;
            Physics::getPhysics().collideX();
        }
    }
    // Check for clipping with tiles to the right.
    if( directionOfMovement > 0 && directionOfMovement < 8 &&
            floor( oldX + rightClip ) < floor( newX + rightClip ) ) {
        Tile topTile = WorldData::getWorldData().getTile( 
            floor( newX + rightClip ), floor( oldY + topClip ) );
        Tile bottomTile = WorldData::getWorldData().getTile( 
            floor( newX + rightClip ), floor( oldY + bottomClip ) );
        if( ( topTile.getType() != Tile::Air && 
            topTile.getType() != Tile::Surface ) 
            || ( bottomTile.getType() != Tile::Air && 
            bottomTile.getType() != Tile::Surface ) ) {
            newX = floor( oldX + 1 ) - 0.001 - rightClip;
            Physics::getPhysics().collideX();
        }
    }
    // Check for clipping with tiles above.
    if( ( directionOfMovement < 4 || directionOfMovement > 12 ) &&
            floor( oldY + topClip ) < floor( newY + topClip ) ) {
        Tile leftTile = WorldData::getWorldData().getTile( 
            floor( newX + leftClip ), floor( newY + topClip ) );
        Tile rightTile = WorldData::getWorldData().getTile( 
            floor( newX + rightClip ), floor( newY + topClip ) );
        if( ( leftTile.getType() != Tile::Air && 
            leftTile.getType() != Tile::Surface ) 
            || ( rightTile.getType() != Tile::Air && 
            rightTile.getType() != Tile::Surface ) ) {
            newY = floor( oldY + 1 ) - 0.001 - topClip;
            Physics::getPhysics().collideY();
        }
    }
    // Check for clipping with tiles below.
    if( directionOfMovement > 4 && directionOfMovement < 12 &&
            floor( oldY + bottomClip ) > floor( newY + bottomClip ) ) {
        Tile& leftTile = WorldData::getWorldData().getTile( 
            floor( newX + leftClip ), floor( newY + bottomClip ) );
        Tile& rightTile = WorldData::getWorldData().getTile( 
            floor( newX + rightClip ), floor( newY + bottomClip ) );
        // Test if the player is trying to dig.
        if( InputHandler::getDirectionOfMovement() >= 7 && 
                InputHandler::getDirectionOfMovement() <= 9 &&
                onGround == DIG_DELAY ) {
            float offSet = oldX - floor( oldX );
            // Dig the tile that the player is more over, or neither if they 
            // are too close to the middle.
            if( offSet > 0.2 && offSet <= 0.5 && Tile::diggable(rightTile) ) {
                rightTile.dig();
            } else if( offSet > 0.5 && offSet <= 0.8 && Tile::diggable(leftTile) ) {
                leftTile.dig();
            }
        }
        // Do the actual clipping.
        if( ( leftTile.getType() != Tile::Air && 
                leftTile.getType() != Tile::Surface ) 
                || ( rightTile.getType() != Tile::Air && 
                rightTile.getType() != Tile::Surface ) ) {
            newY = floor( oldY ) - bottomClip + 0.001;
            Physics::getPhysics().collideY();
            if( onGround < DIG_DELAY ) onGround++;
        } else onGround = 0;
    } else onGround = 0;
    position = sf::Vector2f( newX, newY );
}

Player Player::singleton = Player();

Player::Player(void) {
    position = sf::Vector2f( 1.0f, 1.0f );
    topClip = 0.45;
    bottomClip = -0.45;
    leftClip = -0.45;
    rightClip = 0.45;
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