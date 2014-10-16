#include "Missile.h"
#include "redspace.h"

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

Missile::Missile(float x, float y, bool active,RedSpace* game) {
	explosionOn = false;
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
	this->game = game;
	this->timeSinceLastSmoke = 0;
	this->age = 0;
	setColorFilter(graphicsNS::WHITE);
}


void Missile::update(float frameTime)
{
	if(!active)
		return;

    Actor::update(frameTime);

	age += frameTime;
	if(age >= missileNS::LIFESPAN)
	{
		setActive(false);
	}

	timeSinceLastSmoke+=frameDelay;
	if(timeSinceLastSmoke >= missileNS::SMOKE_DELAY)
	{
		game->spawnSmokeParticle(*getCenter());
		timeSinceLastSmoke = 0;
	}

	//Graphics::Vector2Normalize(&gravityV);

	float changeX = frameTime * this->velocity.x;
	float changeY = frameTime * this->velocity.y;

    spriteData.angle = atan2(changeX,-changeY); // rotate the ship
	//spriteData.angle = Graphics::Vector2Normalize(&velocity);
    spriteData.x += changeX;    // move ship along X 
    spriteData.y += changeY;     // move ship along Y

	if(explosionOn)
    {
        explosion.update(frameTime);
        if(explosion.getAnimationComplete())    // if explosion animation complete
        {
            explosionOn = false;                // turn off explosion
            visible = false;
			explosion.setActive(false);
            explosion.setAnimationComplete(false);
            explosion.setCurrentFrame(EXP_START);
        }
    }
}

void Missile::draw() {
    if(explosionOn) {
		explosion.setCenterX(spriteData.x);
		explosion.setCenterY(spriteData.y);
        explosion.draw(spriteData); // draw explosion using current spriteData
	}
    if(active)
        Actor::draw(getColorFilter());              // draw ship
}


void  Missile::setActive(bool a) {
		active = a;
		if(!a) {				
			explosionOn = true;
			explosion.activate();
		}
}

void Missile::activate()
{
	active = true;
	age = 0;
}