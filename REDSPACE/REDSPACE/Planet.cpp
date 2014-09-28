#include "Planet.h"

Planet::Planet() {
	//	    radius = 1.0;
	//    edge.left = -1;
	//    edge.top = -1;
	//    edge.right = 1;
	//    edge.bottom = 1;
	//    mass = 1.0;
	//    velocity.x = 0.0;
	//    velocity.y = 0.0;
	//    deltaV.x = 0.0;
	//    deltaV.y = 0.0;
	//    active = true;                  // the entity is active
	//    rotatedBoxReady = false;
	//    collisionType = CIRCLE;
	//    health = 100;
	//    gravity = 6.67428e-11f;
	//
	//	const int   WIDTH = 128;                // image width
	//    const int   HEIGHT = 128;               // image height
	//    const int   COLLISION_RADIUS = 120/2;   // for circular collision
	//    const int   X = GAME_WIDTH/2 - WIDTH/2; // location on screen
	//    const int   Y = GAME_HEIGHT/2 - HEIGHT/2;
	//    const float MASS = 1.0e14f;             // mass
	//    const int   TEXTURE_COLS = 1;           // texture has 1 column
	//    const int   START_FRAME = 0;            // starts at frame 0
	//    const int   END_FRAME = 0;              // no animation
	//
	//    spriteData.x    = X;              // location on screen
	//    spriteData.y    = Y;
	//    radius          = COLLISION_RADIUS;
	//    mass            = MASS;
	//    startFrame      = START_FRAME;    // first frame of ship animation
	//    endFrame        = END_FRAME;      // last frame of ship animation
	//    setCurrentFrame(startFrame);
	//    //startFrame      = planetNS::START_FRAME;    // first frame of ship animation
	//    //endFrame        = planetNS::END_FRAME;      // last frame of ship animation
	//    //setCurrentFrame(startFrame);
	//
	//    edge.left = -1;
	//    edge.top = -1;
	//    edge.right = 1;
	//    edge.bottom = 1;
	//    this->mass = mass;
	//    velocity.x = 0.0;
	//    velocity.y = 0.0;
	//    deltaV.x = 0.0;
	//    deltaV.y = 0.0;
	//    this->active = active;                  // the entity is active
	//    rotatedBoxReady = false;
	//    collisionType = CIRCLE;
	//    health = 100;
	//    gravity = 100;
}

Planet::Planet(float x, float y, float rad, float mass, 
			   float xVel, float yVel, float xDel, float yDel, bool active = true){
				   spriteData.x    = x;              // location on screen
				   spriteData.y    = y;
				   radius          = rad;
				   //startFrame      = planetNS::START_FRAME;    // first frame of ship animation
				   //endFrame        = planetNS::END_FRAME;      // last frame of ship animation
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