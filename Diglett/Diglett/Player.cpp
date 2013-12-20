#include "Player.h"
#include <iostream>
#include "Tile.h"
#include "WorldData.h"
#include "InputHandler.h"


Player& Player::getPlayer() {
    return singleton;
}

sf::Vector2f Player::getPosition() {
    return position;
}

void Player::move( float x, float y ) {
    // The program will crash if attempting to load a chunk outside the world.
    // Constrain movement until infinite worlds are implemented.
    if( position.x + x > 150 || position.x + x < -150 
        || position.y + y > 150 || position.y + y < -150 ) 
        return;
    // Check for collisions.
    float oldX = position.x;
    float oldY = position.y;
    float newX = oldX + x;
    float newY = oldY + y;
    // Check for clipping with tiles to the left.
    if( floor( oldX + leftClip ) > floor( newX + leftClip ) ) {
        Tile topTile = WorldData::getWorldData().getTile( 
            floor( newX + leftClip ), floor( oldY + topClip ) );
        Tile bottomTile = WorldData::getWorldData().getTile( 
            floor( newX + leftClip ), floor( oldY + bottomClip ) );
        if( ( topTile.getType() != Tile::Air && 
            topTile.getType() != Tile::Surface ) 
            || ( bottomTile.getType() != Tile::Air && 
            bottomTile.getType() != Tile::Surface ) ) {
            newX = floor( oldX ) - leftClip;
        }
    }
    // Check for clipping with tiles to the right.
    if( floor( oldX + rightClip ) < floor( newX + rightClip ) ) {
        Tile topTile = WorldData::getWorldData().getTile( 
            floor( newX + rightClip ), floor( oldY + topClip ) );
        Tile bottomTile = WorldData::getWorldData().getTile( 
            floor( newX + rightClip ), floor( oldY + bottomClip ) );
        if( ( topTile.getType() != Tile::Air && 
            topTile.getType() != Tile::Surface ) 
            || ( bottomTile.getType() != Tile::Air && 
            bottomTile.getType() != Tile::Surface ) ) {
            newX = floor( oldX + 1 ) - 0.001 - rightClip;
        }
    }
    // Check for clipping with tiles above.
    if(  floor( oldY + topClip ) < floor( newY + topClip ) ) {
        Tile leftTile = WorldData::getWorldData().getTile( 
            floor( newX + leftClip ), floor( newY + topClip ) );
        Tile rightTile = WorldData::getWorldData().getTile( 
            floor( newX + rightClip ), floor( newY + topClip ) );
        if( ( leftTile.getType() != Tile::Air && 
            leftTile.getType() != Tile::Surface ) 
            || ( rightTile.getType() != Tile::Air && 
            rightTile.getType() != Tile::Surface ) ) {
            newY = floor( oldY + 1 ) - 0.001 - topClip;
        }
    }
    // Check for clipping with tiles below.
    if( floor( oldY + bottomClip ) > floor( newY + bottomClip ) ) {
        Tile& leftTile = WorldData::getWorldData().getTile( 
            floor( newX + leftClip ), floor( newY + bottomClip ) );
        Tile& rightTile = WorldData::getWorldData().getTile( 
            floor( newX + rightClip ), floor( newY + bottomClip ) );
        if( ( leftTile.getType() != Tile::Air && 
            leftTile.getType() != Tile::Surface ) 
            || ( rightTile.getType() != Tile::Air && 
            rightTile.getType() != Tile::Surface ) ) {
            newY = floor( oldY ) - bottomClip;
        }
    }
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
