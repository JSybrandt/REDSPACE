#include "Missile.h"

Missile::Missile() {
    spriteData.width = missileNS::WIDTH;           // size of Ship1
    spriteData.height = missileNS::HEIGHT;
    spriteData.x = missileNS::X;                   // location on screen
    spriteData.y = missileNS::Y;
    spriteData.rect.bottom = missileNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = missileNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 0;                             // velocity Y
	deltaV.x = 0.0;
    deltaV.y = 0.0;
    frameDelay = missileNS::SHIP_ANIMATION_DELAY;
    startFrame = missileNS::SHIP_START_FRAME;      // first frame of ship animation
    endFrame     = missileNS::SHIP_END_FRAME;      // last frame of ship animation
    currentFrame = startFrame;
    radius = missileNS::WIDTH/2.0;
    mass = missileNS::MASS;
    collisionType = CIRCLE;
	gravity = 6.67428e-11f;
}

Missile::Missile(float x, float y) {
    spriteData.width = missileNS::WIDTH;           // size of Ship1
    spriteData.height = missileNS::HEIGHT;
    spriteData.x = x;                   // location on screen
    spriteData.y = y;
    spriteData.rect.bottom = missileNS::HEIGHT;    // rectangle to select parts of an image
    spriteData.rect.right = missileNS::WIDTH;
    velocity.x = 0;                             // velocity X
    velocity.y = 10;                             // velocity Y
	deltaV.x = 0.0;
    deltaV.y = 0.0;
    frameDelay = missileNS::SHIP_ANIMATION_DELAY;
    startFrame = missileNS::SHIP_START_FRAME;      // first frame of ship animation
    endFrame     = missileNS::SHIP_END_FRAME;      // last frame of ship animation
    currentFrame = startFrame;
    radius = missileNS::WIDTH/2.0;
    mass = missileNS::MASS;
    collisionType = CIRCLE;
	gravity = 6.67428e-11f;
}

Missile::Missile(float x, float y, float rad, float mass, 
			   float xVel, float yVel, float xDel, float yDel, bool active = true){
				   spriteData.x    = x;              // location on screen
				   spriteData.y    = y;
				   radius          = rad;
				   //startFrame      = planetNS::START_FRAME;    // first frame of ship animation
				   //endFrame        = planetNS::END_FRAME;      // last frame of ship animation
				   //setCurrentFrame(startFrame);

				   this->mass = mass;
				   velocity.x = 0.0;
				   velocity.y = 0.0;
				   deltaV.x = 0.0;
				   deltaV.y = 0.0;
				   this->active = active;                  // the entity is active
				   rotatedBoxReady = false;
				   collisionType = BOX;
				   health = 100;
				   gravity = 6.67428e-11f;

}

void Missile::update(float frameTime)
{
    Actor::update(frameTime);
    spriteData.angle += frameTime * missileNS::ROTATION_RATE;  // rotate the ship
    spriteData.x += frameTime * this->velocity.x;     // move ship along X 
    spriteData.y += frameTime * this->velocity.y;     // move ship along Y

    // Bounce off walls
    // if hit right screen edge
    if (spriteData.x > GAME_WIDTH-missileNS::WIDTH*getScale())
    {
        // position at right screen edge
        spriteData.x = GAME_WIDTH-missileNS::WIDTH*getScale();
        velocity.x = -velocity.x;               // reverse X direction
    } 
    else if (spriteData.x < 0)                  // else if hit left screen edge
    {
        spriteData.x = 0;                       // position at left screen edge
        velocity.x = -velocity.x;               // reverse X direction
    }
    // if hit bottom screen edge
    if (spriteData.y > GAME_HEIGHT-missileNS::HEIGHT*getScale())
    {
        // position at bottom screen edge
        spriteData.y = GAME_HEIGHT-missileNS::HEIGHT*getScale();
        velocity.y = -velocity.y;               // reverse Y direction
    }
    else if (spriteData.y < 0)                  // else if hit top screen edge
    {
        spriteData.y = 0;                       // position at top screen edge
        velocity.y = -velocity.y;               // reverse Y direction
    }
}
