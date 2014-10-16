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
	P2Controls = Controls(VK_UP,VK_DOWN,VK_LEFT,VK_RIGHT);
	sun = Planet(GAME_WIDTH/2 - 128/2.0, GAME_HEIGHT/2 - 120/2.0, 70/2.0,5.0e14f,true);
	earth = PlayerPlanet(GAME_WIDTH/3 - 128/2.0, GAME_HEIGHT/2 - 120/2.0, 100, 5.0e14f,this,P1Controls);
	mars = PlayerPlanet(GAME_WIDTH/3 - 128/2.0, GAME_HEIGHT/2 - 120/2.0, 100, 5.0e14f,this,P2Controls);
	misStorage = 0;
	partStorage = 0;
	shotStorage = 0;
	numActiveMissles = 0;
	numActiveParticles = 0;
	numActiveShot = 0;
	NewsLocation = GAME_WIDTH;
	currentNewsIndex = rand()%NUM_NEWS_ITEMS;
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

	srand(time(0));

	//	Explosion texture
	if (!explosionTex.initialize(graphics,EXP_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing nebula texture"));

	// Planet texture
	if (!planetTexture.initialize(graphics,PLANET_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sun texture"));
	if (!marsTex.initialize(graphics,MARS_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mars texture"));
	if (!earthTex.initialize(graphics,EARTH_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing earth texture"));

	// Other Textures
	if (!misTexture.initialize(graphics,MISSILE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing ship texture"));

	if(!cursorTex.initialize(graphics,CURSOR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing cursor texture"));
	if(!smokeTex.initialize(graphics,SMOKE_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing smoke texture"));
	if(!shotTex.initialize(graphics,SHOT_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing shot texture"));

	if(!barTex.initialize(graphics,BAR_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bar texture"));
	if(!astTex.initialize(graphics,AST_IMAGE))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing bar texture"));

	//Bars
	if (!marsBar.initialize(graphics,0,0,0,&barTex))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mars bar"));

	if (!earthBar.initialize(graphics,0,0,0,&barTex))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing earth bar"));

	marsBar.setX(GAME_WIDTH-marsBar.getWidth());
	earthBar.setX(0);

	// Planets
	if (!sun.initialize(this,0,0,0,&planetTexture))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing sun"));
	if (!mars.initialize(this,0,0,0,&marsTex))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing mars"));
	if (!earth.initialize(this,0,0,0,&earthTex))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing earth"));


	mars.setCursor(&cursorTex);
	earth.setCursor(&cursorTex);

	mars.setColorFilter(graphicsNS::RED);
	earth.setColorFilter(graphicsNS::BLUE);

	sun.setX(GAME_WIDTH*0.5f  - sun.getWidth()*0.5f);
	sun.setY(GAME_HEIGHT*0.5f - sun.getHeight()*0.5f);
	sun.setMass(5e14f);
	sun.setGravity(2.17428e-21f);
	//sun.setResistance(.0001);

	mars.setCenterX(GAME_WIDTH*0.2f);
	mars.setCenterY(GAME_HEIGHT*0.5f);

	mars.setMass(9e13f);
	mars.setVelocity(VECTOR2(0,155)); //@ 1/4 distance, y = 130.
	mars.setGravity(2.17428e-22f); //-16 for 000001

	earth.setCenterX(GAME_WIDTH*0.7f);
	earth.setCenterY(GAME_HEIGHT*0.5f );

	earth.setMass(9e13f);
	earth.setVelocity(VECTOR2(0,-190)); //@ 1/4 distance, y = 130.
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
		mc[i].setMass(1450);
		mc[i].setVelocity(D3DXVECTOR2(0,-360-(rand()%100)));
		//mc[i].setCollisionRadius(32);
		mc[i].explosion.initialize(this, 32, 32, 2, &explosionTex);
		mc[i].explosion.setFrames(EXP_START, EXP_END);
		mc[i].explosion.setCurrentFrame(EXP_START);
		mc[i].explosion.setFrameDelay(EXP_DELAY);
		mc[i].explosion.setLoop(false);               // do not loop animation
		mc[i].explosion.setMass(-mc[i].getMass()*40000000000);
		//spaceBorn++;
	}
	float degrees = 360;
	float divisor = 360/ASTMAX;
	const float REDUCE = 7.7;
	const float RADIUS = 500;
	for(int i = 0; i < ASTMAX; i++) { //NEEDS TO MAKE ACTIVE ONLY

		VECTOR2 loc(1,0);
		loc *=  GAME_WIDTH*4/10 + (rand()%100/100.0)*GAME_WIDTH/10;

		float spawnDirection = float(i)/ASTMAX * 2*PI;
		float nx = cos(spawnDirection)*loc.x - sin(spawnDirection)*loc.y;
		float ny = sin(spawnDirection)*loc.x + cos(spawnDirection)*loc.y;
		loc.x=nx;loc.y=ny;

		loc += *sun.getCenter();

		astField[i] = Asteroid(loc.x, loc.y, 20/2.0,5.0e3f,true);
		astField[i].initialize(this, 0, 0, 0, &astTex);

		float direction = -PI/2;
		D3DXVECTOR2 vel = *astField[i].getCenter() - *sun.getCenter();
		D3DXVec2Normalize(&vel,&vel);
		vel *= 600;
		nx = cos(direction)*vel.x - sin(direction)*vel.y;
		ny = sin(direction)*vel.x + cos(direction)*vel.y;
		vel.x = nx; vel.y=ny;
		astField[i].setVelocity(vel);
		//astField[i].setResistance(.014); //.014
	}


	for(int i = 0; i < PARTICLEMAX; i++) { //NEEDS TO MAKE ACTIVE ONLY
		particles[i] = SmokeParticle();
		particles[i].initialize(this, 0,0, 0, &smokeTex);
		//spaceBorn++;
	}

	for(int i = 0 ; i < SHOTMAX; i++) //Shot Spawner
	{
		shots[i] = Shot();
		shots[i].initialize(this,0,0,0,&shotTex);
	}

	if(!earthText.initialize(graphics,50,true,false,"Copperplate Gothic")) 
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Constantia Font"));
	if(!marsText.initialize(graphics,50,true,false,"Copperplate Gothic"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing Constantia Font"));
	if(!NewsText.initialize(graphics,25,false,false,"Courier New"))
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing news Font"));


	earthText.setFontColor(graphicsNS::BLUE);
	marsText.setFontColor(graphicsNS::RED);
	NewsText.setFontColor(graphicsNS::WHITE);
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
			//mars.gravityForce(&mc[i].explosion, frameTime); //TESTING ONLY
			//earth.gravityForce(&mc[i].explosion, frameTime); //TESTING ONLY
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
	for(int i = 0 ; i < SHOTMAX; i++)
	{
		shots[i].update(frameTime);
	}
	for(int i = 0 ; i < ASTMAX; i++)
	{
		for(int j = 0; j < MISSILEMAX; j++) {
			if(mc[j].explosionOn) {
				astField[i].gravityForce(&mc[j].explosion, frameTime);
			}
		}
		astField[i].update(frameTime);
		astField[i].gravityForce(&sun, frameTime);
	}

	sun.update(frameTime);
	mars.update(frameTime);
	earth.update(frameTime);


	marsBar.setY((playerPlanetNS::MAX_RESOURCE-mars.getResource())/playerPlanetNS::MAX_RESOURCE*GAME_HEIGHT);
	earthBar.setY((playerPlanetNS::MAX_RESOURCE-earth.getResource())/playerPlanetNS::MAX_RESOURCE*GAME_HEIGHT);

	if(earth.getResource() < playerPlanetNS::NUKE_COST)
		earthBar.setColorFilter(graphicsNS::BLUE & graphicsNS::ALPHA50 );
	else
		earthBar.setColorFilter(graphicsNS::BLUE);

	if(mars.getResource() < playerPlanetNS::NUKE_COST)
		marsBar.setColorFilter(graphicsNS::RED  & graphicsNS::ALPHA50 );
	else
		marsBar.setColorFilter(graphicsNS::RED);

	updateNews();
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

		//if hit by a shot
		bool hitShot = false;
		for(int k = 0; k < SHOTMAX; k++){if(mc[i].collidesWith(shots[k],collison)){hitShot=true; shots[k].setActive(false);break;}}

		bool hitAst = false;
		//if hit asteroid
		for(int k = 0; k < ASTMAX; k++){
			if(mc[i].collidesWith(astField[k],collison)){
				hitAst = true;
				break;
			}
		}

		bool hitEarth = mc[i].collidesWith(earth,collison);
		bool hitMars = mc[i].collidesWith(mars,collison);

		if(mc[i].getActive() && (mc[i].collidesWith(sun,collison) || hitEarth || hitMars || hitShot||hitAst)) {

			mc[i].setActive(false);
			numActiveMissles--;

			int peopleDead = rand()%100000000+783000000;
			if(hitEarth)earth.killPeople(peopleDead);
			if(hitMars)mars.killPeople(peopleDead);

			audio->playCue(SC_HIT);


		}

	}

	for(int i = 0 ; i < SHOTMAX; i++)
	{
		VECTOR2 collison;
		bool hitEarth = shots[i].collidesWith(earth,collison);
		bool hitMars = shots[i].collidesWith(mars,collison);
		if(shots[i].collidesWith(sun,collison)||hitEarth||hitMars)
		{
			shots[i].setActive(false);
			int peopleDead = rand()%100000+1000000;
			if(hitEarth)earth.killPeople(peopleDead);
			if(hitMars)
				mars.killPeople(peopleDead);
		}
	}

	for(int i = 0 ; i < ASTMAX; i++) { //Asteroid field collision with planets
		VECTOR2 collison;
		//if hit by a shot
		bool hitShot = false;
		for(int k = 0; k < SHOTMAX; k++){if(astField[i].collidesWith(shots[k],collison)){hitShot=true; shots[k].setActive(false);}}
		bool hitEarth = astField[i].collidesWith(earth,collison);
		bool hitMars = astField[i].collidesWith(mars,collison);
		if(astField[i].collidesWith(sun,collison)||hitEarth||hitMars||hitShot)
		{
			astField[i].setActive(false);
			if(hitEarth){
				earth.killPeople(rand()%100000+5000000);
				audio->playCue(SC_CRASH);
			}
			if(hitMars){
				mars.killPeople(rand()%1000000+5000000);
				audio->playCue(SC_CRASH);
			}
		}

	}


}

//=============================================================================
// Render game items
//=============================================================================
void RedSpace::render()
{
	graphics->spriteBegin();                // begin drawing sprites

	if(earth.getPopulation()>0 && mars.getPopulation()==0)
	{
		earthText.print("TERRAN VICTORY",GAME_WIDTH/6,GAME_HEIGHT/2);
	}
	else if(earth.getPopulation()==0 && mars.getPopulation()>=0)
	{
		marsText.print("MARTIAN VICTORY",GAME_WIDTH/6,GAME_HEIGHT/2);
	}
	else
	{
		for(int i = 0; i < PARTICLEMAX; i++) {
			particles[i].draw();
		}
		for(int i = 0; i < SHOTMAX; i++) {
			if(shots[i].getActive())shots[i].draw();
		}
		for(int i = 0; i < MISSILEMAX; i++) {
			mc[i].draw();
		}
		for(int i = 0; i < ASTMAX; i++) {
			astField[i].draw();
		}
		//ship.draw();                            // add the spaceship to the scene

		sun.draw();
		mars.draw();// add the sun to the scene
		earth.draw();

		NewsText.print(NEWS[currentNewsIndex],NewsLocation,0);

		marsBar.draw(marsBar.getColorFilter());
		earthBar.draw(earthBar.getColorFilter());

	}

	earthText.print(popWithLeadingZeros(earth.getPopulation()),GAME_WIDTH/6,GAME_HEIGHT*7/8);
	marsText.print(popWithLeadingZeros(mars.getPopulation()),GAME_WIDTH*4/6,GAME_HEIGHT*7/8);


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


void RedSpace::spawnMissle(D3DXVECTOR2 location, D3DXVECTOR2 velocity, COLOR_ARGB color)
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
			mc[misStorage].setColorFilter(color);
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


void RedSpace::spawnShot(D3DXVECTOR2 location, D3DXVECTOR2 velocity)
{
	for(int i = 0; i < SHOTMAX; i++)
	{
		if(shotStorage == SHOTMAX) {
			shotStorage = 0;
		}
		if(!shots[shotStorage].getActive()){
			shots[shotStorage].spawn(location.x,location.y,velocity.x,velocity.y);
			shotStorage++;
			numActiveShot++;
			break;
		}
		shotStorage++;
	}
}


void RedSpace::updateNews()
{
	NewsLocation -= SCROLL_SPEED * frameTime;
	if(NewsLocation < -int(GAME_WIDTH))
	{
		int old = currentNewsIndex;
		while(old==currentNewsIndex)
			currentNewsIndex = rand()%NUM_NEWS_ITEMS;
		NewsLocation = GAME_WIDTH;
	}
}

string RedSpace::popWithLeadingZeros(long long int in)
{
	string current = std::to_string(in);
	while(current.length() < 11) current = "0"+current;
	return current;
}