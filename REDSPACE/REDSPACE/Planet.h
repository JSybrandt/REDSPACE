#include "Actor.h"

class Planet: public Actor
{
public:
	Planet();
	Planet(float x, float y, float rad, float mass, 
			   float xVel, float yVel, float xDel, float yDel, bool active);

};