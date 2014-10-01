#include "Missile.h"

Missile::Missile() {
	explosionOn = false;
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

Missile::Missile(float x, float y, bool active) {
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
	this->active = active;
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
	if(!active)
		return;

    Actor::update(frameTime);
	//Graphics::Vector2Normalize(&gravityV);
    spriteData.angle += frameTime * missileNS::ROTATION_RATE;  // rotate the ship
	//spriteData.angle = Graphics::Vector2Normalize(&velocity);
    spriteData.x += frameTime * this->velocity.x;     // move ship along X 
    spriteData.y += frameTime * this->velocity.y;     // move ship along Y

	if(explosionOn)
    {
        explosion.update(frameTime);
        if(explosion.getAnimationComplete())    // if explosion animation complete
        {
            explosionOn = false;                // turn off explosion
            visible = false;
            explosion.setAnimationComplete(false);
            explosion.setCurrentFrame(EXP_START);
        }
    }
}

void Missile::draw() {
    if(explosionOn)
        explosion.draw(spriteData); // draw explosion using current spriteData
    if(active)
        Actor::draw();              // draw ship
}
