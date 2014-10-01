#include "Actor.h"
#include "constants.h"

namespace explosionNS
{
    const int WIDTH = 64;                   // image width
    const int HEIGHT = 64;                  // image height
    const int   TEXTURE_COLS = 2;           // texture has 2 columns
    const int   EXPLOSION_START_FRAME = 0;       // ship starts at frame 0
    const int   EXPLOSION_END_FRAME = 3;         // ship animation frames 0,1,2,3
    const float EXPLOSION_ANIMATION_DELAY = 0.2f; // time between frames
}

class Explosion: public Actor
{
public:
	Explosion();
	~Explosion() {}
	Explosion(float x, float y, bool active);

	void update(float frameTime);
};
