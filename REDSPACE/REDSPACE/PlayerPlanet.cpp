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
}

void PlayerPlanet::update(float frameTime)
{
	Planet::update(frameTime);
	if(input->wasKeyPressed(controls.up))
	{

		D3DXVECTOR2 aim(1,0);
		float nx = cos(cursorLocation)*aim.x - sin(cursorLocation)*aim.y;
		float ny = sin(cursorLocation)*aim.x + cos(cursorLocation)*aim.y;
		aim.x = nx; aim.y=ny;
		//D3DXVec2Normalize(&aim,&aim);
		D3DXVECTOR2 center = *getCenter();
		center.x-=36;
		center.y-=36;
		D3DXVECTOR2 offset = center + (getWidth()*aim);
		D3DXVECTOR2 loc = center;// + aim;
		D3DXVECTOR2 vel = 700*aim;

		game->spawnMissle(offset,vel);
	}
	if(input->wasKeyPressed(controls.down))
	{
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