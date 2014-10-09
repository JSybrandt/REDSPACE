#include "PlayerPlanet.h"
#include "redspace.h"

PlayerPlanet::PlayerPlanet(float x, float y, float rad, float mass, RedSpace * game, Controls c)
{
	//parent constructor
	Planet::Planet(x,y,rad,mass,true);
	cursorLocation = 0;
	cursorSpeed = 10;
	this->game = game;
	this->controls = c;
}

void PlayerPlanet::update(float frameTime)
{
	Planet::update(frameTime);
	if(input->wasKeyPressed(controls.up))
	{

		D3DXVECTOR2 aim(10,0);
		aim.x = cos(cursorLocation)*aim.x - sin(cursorLocation)*aim.y;
		aim.y= sin(cursorLocation)*aim.x + cos(cursorLocation)*aim.y;
		aim = aim * 10;
		//D3DXVec2Normalize(&aim,&aim);
		D3DXVECTOR2 center = *getCenter();
		D3DXVECTOR2 corner(getX(),getY());
		D3DXVECTOR2 diff = center - corner;
		D3DXVECTOR2 loc = center;// + aim;
		D3DXVECTOR2 vel = aim;

		game->spawnMissle(loc,vel);
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