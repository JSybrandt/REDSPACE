#include "Asteroid.h"

Asteroid::Asteroid() {
	resistance = 1;
}

Asteroid::Asteroid(float x, float y, float rad, float mass, bool active = true){
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

void Asteroid::update(float frameTime) {
	if(active)
		Planet::update(frameTime);
}

void Asteroid::draw() {
	if(active)
		Planet::draw();
}