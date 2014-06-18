#include "Physics.h"
#include "Player.h"
#include "Constants.h"

sf::Vector2f force;
sf::Vector2f acceleration;
sf::Vector2f velocity;
sf::Vector2f previousLocation;

void Physics::updatePlayer( float deltaTime, sf::Vector2f input, 
			Direction directionOfInput, World& world, Player& player ) {
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
    velocity.x += ( acceleration.x * .06f * deltaTime );
    velocity.y += ( acceleration.y * .06f * deltaTime );

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
    player.move( velocity.x, velocity.y, directionOfInput, world );
    
}

void Physics::collideX( Player& player ) {
    velocity.x = -BOUNCE_FACTOR * velocity.x;
    damagePlayerHull( velocity.x, player );
}

void Physics::collideY( Player& player ) {
    velocity.y = -BOUNCE_FACTOR * velocity.y;
    damagePlayerHull( velocity.y, player );
}

void Physics::damagePlayerHull( float velocity, Player& player ) {
    if( velocity >= HULL_DAMAGE_THRESHOLD ) {
        player.damageHull( (int) ( velocity * HULL_DAMAGE_SCALER ) );
    } else if( velocity <= -HULL_DAMAGE_THRESHOLD ) {
        player.damageHull( (int) ( -velocity * HULL_DAMAGE_SCALER ) );
    }
}

void Physics::reset() {
    velocity.x = 0;
    velocity.y = 0;
}

Physics& Physics::getPhysics(){ return singleton; }

Physics Physics::singleton = Physics();

const float Physics::GRAVITY_STRENGTH = 0.003f;
const float Physics::PLAYER_MASS = 1.0f;
const float Physics::HORIZONTAL_AIR_RESISTANCE = 0.05f;
const float Physics::VERTICAL_AIR_RESISTANCE = 0.001f;
const float Physics::MINIMUM_VELOCITY = 0.01f;
const float Physics::BOUNCE_FACTOR = 0.2f;
const float Physics::PLAYER_MAX_SPEED = 0.2f;
const float Physics::HULL_DAMAGE_THRESHOLD = 0.028f;
const float Physics::HULL_DAMAGE_SCALER = 1000.0f;

Physics::Physics(void){
    previousLocation = sf::Vector2f(1.0f,1.0f);
}