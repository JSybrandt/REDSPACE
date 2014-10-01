#include "Explosion.h"

Explosion::Explosion() {
	active = false;
	resistance = 1;
}

Explosion::Explosion(float x, float y, bool active = false){
	spriteData.x    = x;              // location on screen
	spriteData.y    = y;
	//center.x = x;
	//center.y = y;
	//startFrame      = ExplosionNS::START_FRAME;    // first frame of ship animation
	//endFrame        = ExplosionNS::END_FRAME;      // last frame of ship animation
	//setCurrentFrame(startFrame);

	edge.left = -1;
	edge.top = -1;
	edge.right = 1;
	edge.bottom = 1;
	this->mass = mass;
	velocity.x = 0.0;
	velocity.y = 0.0;
	deltaV.x = 0.0;
	deltaV.y = 0.0;
	this->active = active;                  // the entity is active
	rotatedBoxReady = false;
	collisionType = CIRCLE;
	health = 100;
	gravity = 6.67428e-11f;

}

void Explosion::update(float frameTime) {

	if (endFrame - startFrame > 0 && active)          // if animated sprite
    {
        animTimer += frameTime;             // total elapsed time
        if (animTimer > frameDelay)
        {
            animTimer -= frameDelay;
            currentFrame++;
            if (currentFrame < startFrame || currentFrame > endFrame)
            {
                if(loop == true)            // if looping animation
                    currentFrame = startFrame;
                else                        // not looping animation
                {
                    currentFrame = endFrame;
                    animComplete = true;    // animation complete
                }
            }
            setRect();                      // set spriteData.rect
        }
    }
}