#include "Physics.h"
#include "Player.h"
#include "Constants.h"

sf::Vector2f force;
sf::Vector2f acceleration;
sf::Vector2f velocity;
sf::Vector2f previousLocation;

void Physics::updatePlayer( sf::Vector2f input, Direction directionOfInput ) {
    acceleration.x = input.x / PLAYER_MASS;
    acceleration.y = input.y / PLAYER_MASS;

    // Disable downward acceleration by player input.
    if( acceleration.y < 0 ) acceleration.y = 0;

    // Add gravitational force
    acceleration.y -= GRAVITY_STRENGTH;
    
    // Apply constant air resistance
    if ( velocity.x != 0 ) {
        acceleration.x -= (HORIZONTAL_AIR_RESISTANCE * velocity.x);
    }

    //set velocity to 0 if it is close enough that it should be
    if ( input.x == 0 && velocity.x < MINIMUM_VELOCITY && 
            velocity.x > -MINIMUM_VELOCITY ) {
        velocity.x = 0.0f;
        acceleration.x = 0.0f;
    }

    //Apply acceleration
    velocity += acceleration;

    //Cap velocity at PLAYER_MAX_SPEED in both y and x directions
    if( velocity.x > PLAYER_MAX_SPEED ){
        velocity.x = PLAYER_MAX_SPEED;
    } else if ( velocity.x < -PLAYER_MAX_SPEED ){
        velocity.x = -PLAYER_MAX_SPEED;
    }
    if( velocity.y > PLAYER_MAX_SPEED ){
        velocity.y = PLAYER_MAX_SPEED;
    } else if ( velocity.y < -PLAYER_MAX_SPEED ){
        velocity.y = -PLAYER_MAX_SPEED;
    }

    //Move player
    Player::getPlayer().move( velocity.x, velocity.y, directionOfInput );
    
}

void Physics::collideX() {
    velocity.x = -BOUNCE_FACTOR * velocity.x;
    damagePlayerHull( velocity.x );
}

void Physics::collideY() {
    velocity.y = -BOUNCE_FACTOR * velocity.y;
    damagePlayerHull( velocity.y );
}

void Physics::damagePlayerHull( float velocity ) {
    if( velocity >= HULL_DAMAGE_THRESHOLD ) {
        Player::getPlayer().damageHull( velocity * HULL_DAMAGE_SCALER );
    } else if( velocity <= -HULL_DAMAGE_THRESHOLD ) {
        Player::getPlayer().damageHull( -velocity * HULL_DAMAGE_SCALER );
    }
}

void Physics::reset() {
    velocity.x = 0;
    velocity.y = 0;
}

Physics& Physics::getPhysics(){ return singleton; }

Physics Physics::singleton = Physics();

const float Physics::HULL_DAMAGE_THRESHOLD = 0.028;
const float Physics::HULL_DAMAGE_SCALER = 1000;

Physics::Physics(void){
    previousLocation = sf::Vector2f(1.0f,1.0f);
}