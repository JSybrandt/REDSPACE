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
	planet = Planet(GAME_WIDTH/2 - 128/2.0, GAME_HEIGHT/2 - 120/2.0, 70/2.0,5.0e14f,true);
	mars = Planet(GAME_WIDTH/2 - 128/2.0, GAME_HEIGHT/2 - 120/2.0, 10/2.0,5.0e14f,true);
	mars2 = Planet(GAME_WIDTH/2 - 128/2.0, GAME_HEIGHT/2 - 120/2.0, 10/2.0,5.0e14f,true);
	misStorage = 0;
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

	if (!backgroundTex.initialize(graphics,BACKGROUND_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

	//	Explosion texture
	if (!explosionTex.initialize(graphics,EXP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

	// planet texture
	if (!planetTexture.initialize(graphics,PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));
	if (!marsTex.initialize(graphics,MARS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet texture"));

	// spaceship texture
	if (!misTexture.initialize(graphics,MISSILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));

	// planet
	if (!planet.initialize(this,0,0,0,&planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));
	if (!mars.initialize(this,0,0,0,&marsTex))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));
	if (!mars2.initialize(this,0,0,0,&marsTex))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing planet"));

	planet.setX(GAME_WIDTH*0.5f  - planet.getWidth()*0.5f);
	planet.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);
	planet.setMass(5e14f);
	planet.setGravity(2.17428e-21f);
	//planet.setResistance(.0001);

	mars.setX(GAME_WIDTH*0.125f  - planet.getWidth()*0.125f);
	mars.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	mars.setMass(9e13f);
	mars.setVelocity(VECTOR2(0,120)); //@ 1/4 distance, y = 130.
	mars.setGravity(2.17428e-22f); //-16 for 000001

	mars2.setX(GAME_WIDTH*0.875f  - planet.getWidth()*0.875f);
	mars2.setY(GAME_HEIGHT*0.5f - planet.getHeight()*0.5f);

	mars2.setMass(9e13f);
	mars2.setVelocity(VECTOR2(0,-120)); //@ 1/4 distance, y = 130.
	mars2.setGravity(2.17428e-22f); //-16 for 000001
	//mars.setResistance(.000001);

	//mars.setResistance(4360);

	if (!missile.initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &misTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship"));



	for(int i = 0; i < MISSILEMAX; i++) { //NEEDS TO MAKE ACTIVE ONLY
		mc[i] = Missile(GAME_WIDTH/4 - missileNS::WIDTH, GAME_HEIGHT/2 - missileNS::HEIGHT, false);
		mc[i].initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &misTexture);
		mc[i].setMass(1200);
		mc[i].setVelocity(D3DXVECTOR2(0,-360-(rand()%100)));

		mc[i].explosion.initialize(graphics, 32, 32, 2, &explosionTex);
		mc[i].explosion.setFrames(EXP_START, EXP_END);
		mc[i].explosion.setCurrentFrame(EXP_START);
		mc[i].explosion.setFrameDelay(EXP_DELAY);
		mc[i].explosion.setLoop(false);               // do not loop animation
		//spaceBorn++;
	}

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void RedSpace::update()
{
	mars.gravityForce(&planet, frameTime);
	mars2.gravityForce(&planet, frameTime);


	if(spaceBorn < MISSILEMAX) { //NEEDS TO MAKE ACTIVE ONLY input->wasKeyPressed(VK_SPACE) && 
		//while(mc[spaceBorn].getActive())
		
		for(int i = 0; i < MISSILEMAX; i++)
		{
			if(misStorage == MISSILEMAX) {
				misStorage = 0;
			}
			if(!mc[misStorage].getActive()){
				mc[misStorage].setX(GAME_WIDTH/4 - missileNS::WIDTH);
				mc[misStorage].setY(GAME_HEIGHT/2 - missileNS::HEIGHT);
				mc[misStorage].setVelocity(D3DXVECTOR2(0,-240-(rand()%100)));
				//mc[i].setResistance(-1);
				mc[misStorage].activate();
				spaceBorn++;
				misStorage++;
				break;
			}
			misStorage++;
		}

	}
	if(input->wasKeyPressed(VK_UP)) { //NEEDS TO MAKE ACTIVE ONLY
		spaceBorn;
	}

	for(int i = 0; i < MISSILEMAX; i++) {
		//if(mc[i].getActive()) {
			mc[i].gravityForce(&planet, frameTime);
			mc[i].gravityForce(&mars, frameTime);
			mc[i].gravityForce(&mars2, frameTime);
			mc[i].update(frameTime);
		//}
		if(mc[i].explosionOn) {
			mc[i].explosion.update(frameTime);
			if(mc[i].explosion.getAnimationComplete()) {   // if explosion animation complete
				mc[i].explosionOn = false;                // turn off explosion
				mc[i].explosion.setAnimationComplete(false);
				mc[i].explosion.setCurrentFrame(EXP_START);
			}
		}

		//mc[i]->setVelocity(collison);
	}


	planet.update(frameTime);
	mars.update(frameTime);
	mars2.update(frameTime);

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
		if(mc[i].getActive() && (mc[i].collidesWith(planet,collison) || mc[i].collidesWith(mars,collison) || mc[i].collidesWith(mars2,collison) )) {
			mc[i].setActive(false);

			//exp[i].setX(mc[i].getX());
			//exp[i].setY(mc[i].getY());
			//exp[i].setActive(true);
			//exp[i].setFrames(EXP_START, EXP_END);   // animation frames
			//exp[i].setCurrentFrame(EXP_START);     // starting frame

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
	planet.draw();
	mars.draw();// add the planet to the scene
	mars2.draw();
	for(int i = 0; i < MISSILEMAX; i++) {
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
