
#pragma once
#include "Planet.h"

class Asteroid: public Planet
{
private:
	float dir;
public:
	Asteroid();
	Asteroid(float x, float y, float rad, float mass, bool active);
	void update(float frameTime);
	void draw();
};