#ifndef PLAYERPLANET_H
#define PLAYERPLANET_H


#include "Planet.h"
#include "Controls.h"

class RedSpace;

namespace playerPlanetNS
{
	const float SHOT_DELAY = 0.05;
	const float NUKE_DELAY = 0.3;
	const long long int STARTING_POP = 10000000000;
	const float CURSOR_INACURACY = PI/8;
	const float MAX_RESOURCE = 100;
	const float NUKE_COST = 40;
	const float SHOT_COST = 3;
	const float RECHARGE_RATE = 25;
	const float CURSOR_SPEED = 5*PI/2;
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
	float getResource(){return currentResource;}
private:

	//aiming location in radians
	float cursorLocation;
	//current ammo bar level
	float ammoLevel;
	
	Image cursor;
	RedSpace* game;
	Controls controls;
	float coolDown;
	long long int displayedPopulation;
	long long int population;
	long long int delPop;
	float currentResource;
	float displayedResource;
};
#endif