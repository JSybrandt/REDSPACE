
#pragma once
#include "Planet.h"

class Asteroid: public Planet
{
public:
	Asteroid();
	Asteroid(float x, float y, float rad, float mass, bool active);
	void update(float frameTime);
	void draw();
};