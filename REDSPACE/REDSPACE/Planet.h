#pragma once
#include "Actor.h"

class Planet: public Actor
{
public:
	Planet();
	Planet(float x, float y, float rad, float mass, bool active);
	void update(float frameTime);
	virtual void draw();
};