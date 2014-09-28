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
	planet = Planet(GAME_WIDTH/2 - 128/2.0, GAME_HEIGHT/2 - 128/2.0, 120/2.0,1.0e14f,0.0,0.0,0.0,0.0,true);
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
	if (!background.initialize(graphics,0,0,0,&backgroundTex))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula"));

	// planet
	if (!planet.initialize(this,0,0,0,&planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));




	planet.setX(GAME_WIDTH*0.5f  - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	if (!missile.initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &misTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));

	//for(int i = 0; i < MISSILEMAX; i++) {
	//	if (!mc[i]->initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &misTexture))
	//		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));
	//}
	// missile.setFrames(missileNS::SHIP_START_FRAME, missileNS::SHIP_END_FRAME);
	//missile.setCurrentFrame(missileNS::SHIP_START_FRAME);
	missile.setX(GAME_WIDTH/4 - missileNS::WIDTH);
	missile.setY(GAME_HEIGHT/2 - missileNS::HEIGHT);
	missile.setVelocity(VECTOR2(0,-missileNS::SPEED)); // VECTOR2(X, Y)


	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void RedSpace::update()
{
	missile.gravityForce(&planet, frameTime);

	if(input->wasKeyPressed(VK_SPACE) && spaceBorn < 10) {
		mc[spaceBorn] = new Missile(GAME_WIDTH/4 - missileNS::WIDTH, GAME_HEIGHT/2 - missileNS::HEIGHT);
		mc[spaceBorn]->initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &misTexture);
		spaceBorn++;
	}

	for(int i = 0; i < spaceBorn; i++) {
		mc[i]->gravityForce(&planet, frameTime);
	}
	for(int i = 0; i < spaceBorn; i++) {
		mc[i]->update(frameTime);
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
{}

//=============================================================================
// Render game items
//=============================================================================
void RedSpace::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	background.draw();                          // add the orion nebula to the scene
	planet.draw();                          // add the planet to the scene
	missile.draw();
	for(int i = 0; i < spaceBorn; i++) {
		mc[i]->draw();
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
