#include "Shot.h"

Shot::Shot():Actor()
{
	age = 0;
	radius = 8;

}

Shot::~Shot()
{
}

void Shot::update(float frameTime)
{
	if(getActive())
	{
		if(age > shotNS::MAX_AGE)
			setActive(false);
		age += frameTime;
		D3DXVECTOR2 v = getVelocity();
		setX(getX()+v.x*frameTime);
		setY(getY()+v.y*frameTime);
	}
}

void Shot::spawn(float x, float y, float vX, float vY)
{
	setActive(true);
	age=0; 
	setCenterX(x);
	setCenterY(y);
	setVelocity(D3DXVECTOR2(vX,vY));
}