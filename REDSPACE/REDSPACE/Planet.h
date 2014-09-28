#include "Actor.h"

class Planet: public Actor
{
public:
	Planet();
	Planet(float x, float y, float rad, long left, long top, long right, long bottom, long mass, 
			   float xVel, float yVel, float xDel, float yDel, bool active);

};