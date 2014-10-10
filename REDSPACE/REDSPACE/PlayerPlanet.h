#ifndef PLAYERPLANET_H
#define PLAYERPLANET_H


#include "Planet.h"
#include "Controls.h"

class RedSpace;


class PlayerPlanet : public Planet
{
public:
	PlayerPlanet(){};
	PlayerPlanet(float x, float y, float rad, float mass, RedSpace * game, Controls c);
	void update(float frameTime);
	void modifyCursorLocation(float delta);
	void draw();
	void setCursor(TextureManager * c);
private:

	//aiming location in radians
	float cursorLocation;
	//current ammo bar level
	float ammoLevel;
	float cursorSpeed;
	Image cursor;
	RedSpace* game;
	Controls controls;
};
#endif