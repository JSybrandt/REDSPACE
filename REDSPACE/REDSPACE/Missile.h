#include "Actor.h"
#include "constants.h"

namespace missileNS
{
    const int WIDTH = 60;                   // image width
    const int HEIGHT = 45;                  // image height
    const int X = GAME_WIDTH/2 - WIDTH/2;   // location on screen
    const int Y = GAME_HEIGHT/2 - HEIGHT/2;
    const float ROTATION_RATE = (float)PI/4; // radians per second
    const float SPEED = 100;                // 100 pixels per second
    const float MASS = 300.0f;              // mass
    const int   TEXTURE_COLS = 2;           // texture has 2 columns
    const int   SHIP_START_FRAME = 0;       // ship starts at frame 0
    const int   SHIP_END_FRAME = 3;         // ship animation frames 0,1,2,3
    const float SHIP_ANIMATION_DELAY = 0.2f; // time between frames
}

class Missile: public Actor
{
public:
	Missile();
	~Missile() {}
	Missile(float x, float y, float rad, float mass, 
			   float xVel, float yVel, float xDel, float yDel, bool active);
	Missile(float x, float y, bool active);

	void update(float frameTime);
};
