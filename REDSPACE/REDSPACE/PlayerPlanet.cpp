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

	if(input->wasKeyPressed(controls.up))
	{

		D3DXVECTOR2 aim(1,0);
		float nx = cos(cursorLocation)*aim.x - sin(cursorLocation)*aim.y;
		float ny = sin(cursorLocation)*aim.x + cos(cursorLocation)*aim.y;
		aim.x = nx; aim.y=ny;
		//D3DXVec2Normalize(&aim,&aim);
		D3DXVECTOR2 center = *getCenter();
		//center.x-=36;
		//center.y-=36;
		D3DXVECTOR2 offset = center + ((getWidth()+10)*aim);
		D3DXVECTOR2 loc = center;// + aim;
		D3DXVECTOR2 vel = 700*aim;

		game->spawnMissle(offset,vel);
	}
	if(input->isKeyDown(controls.down))
	{
		if(coolDown == 0)
		{
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
			float shotLoc = cursorLocation + ((rand()%100)/100.0 -.5)*playerPlanetNS::cursorInaccuracy;
			float nx = cos(shotLoc)*aim.x - sin(shotLoc)*aim.y;
			float ny = sin(shotLoc)*aim.x + cos(shotLoc)*aim.y;
			aim.x = nx; aim.y=ny;
			D3DXVECTOR2 center = *getCenter();
			D3DXVECTOR2 offset = center + ((getWidth()+8)*aim);
			D3DXVECTOR2 loc = center;// + aim;
			D3DXVECTOR2 vel = 700*aim;
			game->spawnShot(offset,vel);
		}
	}

	if(input->isKeyDown(controls.left))
	{
		cursorLocation -= cursorSpeed * frameTime;
		//if(cursorLocation <= -2*PI) cursorLocation-=2*PI;		
	}
	if(input->isKeyDown(controls.right))
	{
		cursorLocation += cursorSpeed * frameTime;
		//if(cursorLocation >= 2*PI) cursorLocation-=2*PI;
	}
}

void PlayerPlanet::draw()
{
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