// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Game Engine Part 1
// Chapter 4 RedSpace.cpp v1.0
// RedSpace is the class we create.

#include "redspace.h"

class PlayerPlanet;

//=============================================================================
// Constructor
//=============================================================================
RedSpace::RedSpace()
{
	P1Controls = Controls('W','S','A','D');
	P2Controls = Controls('I','K','J','L');
	numActiveMissles = 0;
	numActiveParticles = 0;
	sun = Planet(GAME_WIDTH/2 - 128/2.0, GAME_HEIGHT/2 - 120/2.0, 70/2.0,5.0e14f,true);
	earth = PlayerPlanet(GAME_WIDTH/2 - 128/2.0, GAME_HEIGHT/2 - 120/2.0, 100, 5.0e14f,this,P1Controls);
	mars = PlayerPlanet(GAME_WIDTH/2 - 128/2.0, GAME_HEIGHT/2 - 120/2.0, 100, 5.0e14f,this,P2Controls);
	misStorage = 0;
	partStorage = 0;
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

	// sun texture
	if (!planetTexture.initialize(graphics,PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sun texture"));
	if (!marsTex.initialize(graphics,MARS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mars texture"));
	if (!earthTex.initialize(graphics,EARTH_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing earth texture"));

	// spaceship texture
	if (!misTexture.initialize(graphics,MISSILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));

	if(!cursorTex.initialize(graphics,CURSOR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cursor texture"));
	if(!smokeTex.initialize(graphics,SMOKE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing smoke texture"));

	// sun
	if (!sun.initialize(this,0,0,0,&planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sun"));
	if (!mars.initialize(this,0,0,0,&marsTex))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sun"));
	if (!earth.initialize(this,0,0,0,&earthTex))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sun"));

	mars.setCursor(&cursorTex);
	earth.setCursor(&cursorTex);

	sun.setX(GAME_WIDTH*0.5f  - sun.getWidth()*0.5f);
	sun.setY(GAME_HEIGHT*0.5f - sun.getHeight()*0.5f);
	sun.setMass(5e14f);
	sun.setGravity(2.17428e-21f);
	//sun.setResistance(.0001);

	mars.setX(GAME_WIDTH*0.125f  - sun.getWidth()*0.125f);
	mars.setY(GAME_HEIGHT*0.5f - sun.getHeight()*0.5f);

	mars.setMass(9e13f);
	mars.setVelocity(VECTOR2(0,120)); //@ 1/4 distance, y = 130.
	mars.setGravity(2.17428e-22f); //-16 for 000001

	earth.setX(GAME_WIDTH*0.875f  - sun.getWidth()*0.875f);
	earth.setY(GAME_HEIGHT*0.5f - sun.getHeight()*0.5f);

	earth.setMass(9e13f);
	earth.setVelocity(VECTOR2(0,-120)); //@ 1/4 distance, y = 130.
	earth.setGravity(2.17428e-22f); //-16 for 000001
	//mars.setResistance(.000001);

	//mars.setResistance(4360);

	earth.setCollisionRadius(earth.getWidth()/2);
	mars.setCollisionRadius(mars.getWidth()/2);


	if (!missile.initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &misTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing missle"));



	for(int i = 0; i < MISSILEMAX; i++) { //NEEDS TO MAKE ACTIVE ONLY
		mc[i] = Missile(GAME_WIDTH/4 - missileNS::WIDTH, GAME_HEIGHT/2 - missileNS::HEIGHT, false,this);
		mc[i].initialize(this, missileNS::WIDTH, missileNS::HEIGHT, missileNS::TEXTURE_COLS, &misTexture);
		mc[i].setMass(1200);
		mc[i].setVelocity(D3DXVECTOR2(0,-360-(rand()%100)));
		//mc[i].setCollisionRadius(32);
		mc[i].explosion.initialize(this, 32, 32, 2, &explosionTex);
		mc[i].explosion.setFrames(EXP_START, EXP_END);
		mc[i].explosion.setCurrentFrame(EXP_START);
		mc[i].explosion.setFrameDelay(EXP_DELAY);
		mc[i].explosion.setLoop(false);               // do not loop animation
		mc[i].explosion.setMass(-mc[i].getMass()*400000000);
		//spaceBorn++;
	}


	for(int i = 0; i < PARTICLEMAX; i++) { //NEEDS TO MAKE ACTIVE ONLY
		particles[i] = SmokeParticle();
		particles[i].initialize(this, 0,0, 0, &smokeTex);
		//spaceBorn++;
	}
	
	if(!earthPopText.initialize(graphics,50,true,false,"Copperplate Gothic")) 
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Constantia Font"));
	if(!marsPopText.initialize(graphics,50,true,false,"Copperplate Gothic"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Constantia Font"));

	earthPopText.setFontColor(graphicsNS::BLUE);
	marsPopText.setFontColor(graphicsNS::RED);

	audio->playCue(SC_BACKGROUND);

	return;
}

//=============================================================================
// Update all game items
//=============================================================================
void RedSpace::update()
{
	mars.gravityForce(&sun, frameTime);
	earth.gravityForce(&sun, frameTime);


	for(int i = 0; i < MISSILEMAX; i++) {
		if(mc[i].getActive()) {
			mc[i].gravityForce(&sun, frameTime);
			mc[i].gravityForce(&mars, frameTime);
			mc[i].gravityForce(&earth, frameTime);
			mc[i].gravityForce(&mc[i].explosion, frameTime);
			mc[i].update(frameTime);
		}
		if(mc[i].explosionOn) {
			mars.gravityForce(&mc[i].explosion, frameTime); //TESTING ONLY
			earth.gravityForce(&mc[i].explosion, frameTime); //TESTING ONLY
			mc[i].explosion.update(frameTime);
			if(mc[i].explosion.getAnimationComplete()) {   // if explosion animation complete
				mc[i].explosionOn = false;                // turn off explosion
				mc[i].explosion.setAnimationComplete(false);
				mc[i].explosion.setCurrentFrame(EXP_START);
			}
		}

		//mc[i]->setVelocity(collison);
	}

	for(int i = 0 ; i < PARTICLEMAX; i++)
	{
		particles[i].update(frameTime);
	}


	sun.update(frameTime);
	mars.update(frameTime);
	earth.update(frameTime);

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
		bool hitEarth = mc[i].collidesWith(earth,collison);
		bool hitMars = mc[i].collidesWith(mars,collison);
		if(mc[i].getActive() && (mc[i].collidesWith(sun,collison) || hitEarth || hitMars )) {

			mc[i].setActive(false);
			numActiveMissles--;

			int peopleDead = rand()%100000000+783000000;
			if(hitEarth)earth.killPeople(peopleDead);
			if(hitMars)mars.killPeople(peopleDead);


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
	sun.draw();
	mars.draw();// add the sun to the scene
	earth.draw();
	for(int i = 0; i < MISSILEMAX; i++) {
			mc[i].draw();
	}
	for(int i = 0; i < PARTICLEMAX; i++) {
			particles[i].draw();
	}
	//ship.draw();                            // add the spaceship to the scene

	earthPopText.print(std::to_string(earth.getPopulation()),GAME_WIDTH/6,GAME_HEIGHT*7/8);
	marsPopText.print(std::to_string(mars.getPopulation()),GAME_WIDTH*4/6,GAME_HEIGHT*7/8);

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


void RedSpace::spawnMissle(D3DXVECTOR2 location, D3DXVECTOR2 velocity)
{
	for(int i = 0; i < MISSILEMAX; i++)
		{
			if(misStorage == MISSILEMAX) {
				misStorage = 0;
			}
			if(!mc[misStorage].getActive()){
				mc[misStorage].setCenterX(location.x);
				mc[misStorage].setCenterY(location.y);
				mc[misStorage].setVelocity(velocity);
				mc[misStorage].activate();
				numActiveMissles++;
				misStorage++;
				audio->playCue(SC_LAUNCH);
				break;
			}
			misStorage++;
		}
}

void RedSpace::spawnSmokeParticle(D3DXVECTOR2 location)
{
	for(int i = 0; i < PARTICLEMAX; i++)
		{
			if(partStorage == PARTICLEMAX) {
				partStorage = 0;
			}
			if(!particles[partStorage].getActive()){
				particles[partStorage].set(location);
				partStorage++;
				numActiveParticles++;
				break;
			}
			partStorage++;
		}
}


