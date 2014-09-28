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
	planet = Planet(GAME_WIDTH/2 - 128/2.0, GAME_HEIGHT/2 - 128/2.0, 120/2.0,-1,-1,1,1,1.0e14f,0.0,0.0,0.0,0.0,true);
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
	//if (!shipTexture.initialize(graphics,SHIP1_IMAGE))
	//	throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));

	// nebula image
	if (!background.initialize(graphics,0,0,0,&backgroundTex))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// planet
	if (!planet.initialize(this,0,0,0,&planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	planet.setX(GAME_WIDTH*0.5f  - planet.getWidth()*0.5f);
    planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);


	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void RedSpace::update()
{}

//=============================================================================
// Artificial Intelligence
//=============================================================================
void RedSpace::ai()
{}

//=============================================================================
// Handle collisions
//=============================================================================
void RedSpace::collisions()
{}

//=============================================================================
// Render game items
//=============================================================================
void RedSpace::render()
{
	 graphics->spriteBegin();                // begin drawing sprites

    background.draw();                          // add the orion nebula to the scene
    planet.draw();                          // add the planet to the scene
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
