#include "PlayerPlanet.h"
#include "redspace.h"

PlayerPlanet::PlayerPlanet(float x, float y, float rad, float mass, RedSpace * game, Controls c)
{
	//parent constructor
	Planet::Planet(x,y,rad,mass,true);
	cursorLocation = 0;
	cursorSpeed = 5;
	this->game = game;
	this->controls = c;
	population = playerPlanetNS::STARTING_POP;
	currentResource = playerPlanetNS::MAX_RESOURCE;
}

void PlayerPlanet::update(float frameTime)
{
	Planet::update(frameTime);

	if(population < displayedPopulation)
	{
		int d =  max(delPop * frameTime,1);
		displayedPopulation -= d;
	}
	if(displayedPopulation < population) displayedPopulation = population;

	if(coolDown > 0)
	{
		coolDown -= frameTime;
	}
	if(coolDown < 0) coolDown = 0;

	if(input->isKeyDown(controls.up) && currentResource >= playerPlanetNS::NUKE_COST && coolDown == 0)
	{
		coolDown = playerPlanetNS::NUKE_DELAY;
		currentResource-=playerPlanetNS::NUKE_COST;

		D3DXVECTOR2 aim(1,0);
		float nx = cos(cursorLocation)*aim.x - sin(cursorLocation)*aim.y;
		float ny = sin(cursorLocation)*aim.x + cos(cursorLocation)*aim.y;
		aim.x = nx; aim.y=ny;
		D3DXVECTOR2 offset = *getCenter() + ((getWidth()+10)*aim);
		D3DXVECTOR2 vel = 700*aim;

		game->spawnMissle(offset,vel,getColorFilter());
	}
	if(input->isKeyDown(controls.down) && currentResource >= playerPlanetNS::SHOT_COST && coolDown == 0)
	{
			currentResource-=playerPlanetNS::SHOT_COST;
			coolDown = playerPlanetNS::SHOT_DELAY;
			if(rand()%2)
			{
				audio->playCue(SC_SHOT1);
			}
			else
			{
				audio->playCue(SC_SHOT2);
			}
			D3DXVECTOR2 aim(1,0);
			float shotLoc = cursorLocation + ((rand()%100)/100.0 -.5)*playerPlanetNS::CURSOR_INACURACY;
			float nx = cos(shotLoc)*aim.x - sin(shotLoc)*aim.y;
			float ny = sin(shotLoc)*aim.x + cos(shotLoc)*aim.y;
			aim.x = nx; aim.y=ny;
			D3DXVECTOR2 offset = *getCenter() + ((getWidth()+8)*aim);
			D3DXVECTOR2 vel = 700*aim;
			game->spawnShot(offset,vel);
	}

	if(input->isKeyDown(controls.left))
	{
		cursorLocation -= cursorSpeed * frameTime;
	}
	if(input->isKeyDown(controls.right))
	{
		cursorLocation += cursorSpeed * frameTime;
	}

	currentResource += playerPlanetNS::RECHARGE_RATE * frameTime;
	currentResource = min(playerPlanetNS::MAX_RESOURCE,currentResource);
}

void PlayerPlanet::draw()
{
	if(currentResource < playerPlanetNS::NUKE_COST)
		Planet::draw((graphicsNS::ALPHA50 | graphicsNS::ALPHA25) & graphicsNS::LTGRAY );
	else
		Planet::draw();
	cursor.setCenterX(this->getCenterX());
	cursor.setCenterY(this->getCenterY());
	cursor.setRadians(cursorLocation);
	cursor.draw();
}

void PlayerPlanet::setCursor(TextureManager * c)
{
	cursor.initialize(this->graphics,0,0,1,c);
}