#include "Actor.h"
#include "constants.h"

class Explosion: public Actor
{
public:
	Explosion();
	~Explosion() {}
	Explosion(float x, float y, bool active);

	void update(float frameTime);
	void explode();
};
