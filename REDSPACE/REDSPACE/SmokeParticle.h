#include "Actor.h"
class SmokeParticle:public Actor
{
private:
	float currentOpacity;
	float dissipationRate;
public:
	SmokeParticle();
	virtual void update(float frametime);
	void set(D3DXVECTOR2 loc);
	virtual void draw();
};