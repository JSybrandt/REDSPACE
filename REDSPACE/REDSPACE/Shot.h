#pragma once

#include "Actor.h"

namespace shotNS
{
	const float MAX_AGE = 0.5;
}

class Shot: public Actor
{
public:
	Shot();
	~Shot();
	void update(float frameTime);
	void spawn(float x, float y, float vX, float vY);
private:
	float age;
};
