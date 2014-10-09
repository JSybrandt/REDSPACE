#include "SmokeParticle.h"

SmokeParticle::SmokeParticle()
{
	currentOpacity = 0;
	active = false;
	dissipationRate = 1;
}

void SmokeParticle::update(float frametime)
{
	if(active)
	{
		currentOpacity -= dissipationRate*frametime;
		if(currentOpacity<=0) active = false;

	}
}

void SmokeParticle::draw()
{
	if(active)
	{
		//TODO:FADE
		Actor::draw();
	}
}


void SmokeParticle::set(D3DXVECTOR2 loc)
{
	active = true;
	currentOpacity = 0.5;
	setCenterX(loc.x);setCenterY(loc.y);
}