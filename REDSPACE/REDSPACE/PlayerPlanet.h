#ifndef PLAYERPLANET_H
#define PLAYERPLANET_H


#include "Planet.h"
#include "Controls.h"

class RedSpace;

namespace playerPlanetNS
{
	const float SHOT_DELAY = 0.075;
	const long long int STARTING_POP = 5000000000;
	const float cursorInaccuracy = PI/8;
}

class PlayerPlanet : public Planet
{
public:
	PlayerPlanet(){};
	PlayerPlanet(float x, float y, float rad, float mass, RedSpace * game, Controls c);
	void update(float frameTime);
	void modifyCursorLocation(float delta);
	void draw();
	void setCursor(TextureManager * c);
	void killPeople(int dead){population = max(0,population-dead); delPop=displayedPopulation-population;}
	long long int getPopulation(){return displayedPopulation;}
private:

	//aiming location in radians
	float cursorLocation;
	//current ammo bar level
	float ammoLevel;
	float cursorSpeed;
	Image cursor;
	RedSpace* game;
	Controls controls;
	float coolDown;
	long long int displayedPopulation;
	long long int population;
	long long int delPop;
};
#endif