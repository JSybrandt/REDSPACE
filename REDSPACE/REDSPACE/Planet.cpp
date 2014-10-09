#include "Planet.h"

Planet::Planet() {
	resistance = 1;
}

Planet::Planet(float x, float y, float rad, float mass, bool active = true){
	spriteData.x    = x;              // location on screen
	spriteData.y    = y;
	radius          = rad;

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

void Planet::update(float frameTime) {
	Actor::update(frameTime);
	spriteData.x += frameTime * this->velocity.x;     // move ship along X 
	spriteData.y += frameTime * this->velocity.y;     // move ship along Y
}