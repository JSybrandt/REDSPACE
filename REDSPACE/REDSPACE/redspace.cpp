// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Game Engine Part 1
// Chapter 4 RedSpace.cpp v1.0
// RedSpace is the class we create.

#include "redspace.h"

//=============================================================================
// Constructor
//=============================================================================
RedSpace::RedSpace()
{
	spaceBorn = 0;
	planet = Planet(GAME_WIDTH/2 - 128/2.0, GAME_HEIGHT/2 - 120/2.0, 80/2.0,1.0e14f,0.0,0.0,0.0,0.0,true);
}

//=============================================================================
// Destructor
//=============================================================================
RedSpace::~RedSpace()
{
	releaseAll();           // call onLostDevice() for every graphics item
}

//=============================================================================
// Initializes the game
// Throws GameError on error
//=============================================================================
void RedSpace::initialize(HWND hwnd)
{
	Game::initialize(hwnd); // throws GameError

	//list[0] = new Image;
	//list[1] = new Planet(GAME_WIDTH/2 - 128/2, GAME_HEIGHT/2 - 128/2, 120/2,-1,-1,1,1,0,0,0,0,true);

	if (!backgroundTex.initialize(graphics,BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

	// planet texture
	if (!planetTexture.initialize(graphics,PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	// spaceship texture
	if (!misTexture.initialize(graphics,MISSILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));

	// nebula image
	//if (!background.initialize(graphics,0,0,0,&backgroundTex))
		//throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// planet
	if (!planet.initialize(this,0,0,0,&planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));


	planet.setX(GAME_WIDTH*0.5f  - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);
	planet.setMass(5e14f);

	if (!missile.initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &misTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));



	for(int i = 0; i < MISSILEMAX; i++) { //NEEDS TO MAKE ACTIVE ONLY
		mc[i] = Missile(GAME_WIDTH/4 - missileNS::WIDTH, GAME_HEIGHT/2 - missileNS::HEIGHT, false);
		mc[i].initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &misTexture);
		mc[i].setVelocity(D3DXVECTOR2(0,-80-(rand()%100)));
		//spaceBorn++;
	}
	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void RedSpace::update()
{
	missile.gravityForce(&planet, frameTime);

	if(input->wasKeyPressed(VK_SPACE) && spaceBorn < MISSILEMAX) { //NEEDS TO MAKE ACTIVE ONLY
		//while(mc[spaceBorn].getActive())
		for(int i = 0; i < MISSILEMAX; i++)
		{
			if(!mc[i].getActive()){
				mc[i].setX(GAME_WIDTH/4 - missileNS::WIDTH);
				mc[i].setY(GAME_HEIGHT/2 - missileNS::HEIGHT);
				mc[i].setVelocity(D3DXVECTOR2(0,-80-(rand()%100)));
				mc[i].activate();
				spaceBorn++;
				break;
			}
		}

	}

	for(int i = 0; i < MISSILEMAX; i++) {
		if(mc[i].getActive()) {
			mc[i].gravityForce(&planet, frameTime);
			mc[i].update(frameTime);
		}
		//mc[i]->setVelocity(collison);
	}


	planet.update(frameTime);
	missile.update(frameTime);

}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void RedSpace::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void RedSpace::collisions()
{
	VECTOR2 collison;
	for(int i = 0; i < MISSILEMAX; i++) {
		if(mc[i].getActive() && mc[i].collidesWith(planet,collison)) {
			mc[i].setActive(false);
			spaceBorn--;
			//mc[i]->damage(PLANET);
		}
	}
}

//=============================================================================
// Render game items
//=============================================================================
void RedSpace::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	//background.draw();                          // add the orion nebula to the scene
	planet.draw();                          // add the planet to the scene
	missile.draw();
	for(int i = 0; i < MISSILEMAX; i++) {
		if(mc[i].getActive())
			mc[i].draw();
	}
	//ship.draw();                            // add the spaceship to the scene

	graphics->spriteEnd();                  // end drawing sprites

}

//=============================================================================
// The graphics device was lost.
// Release all reserved video memory so graphics device may be reset.
//=============================================================================
void RedSpace::releaseAll()
{
	Game::releaseAll();
	return;
}

//=============================================================================
// The grahics device has been reset.
// Recreate all surfaces.
//=============================================================================
void RedSpace::resetAll()
{
	Game::resetAll();
	return;
}
