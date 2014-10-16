// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 4 spacewar.h v1.0

#ifndef _REDSPACE_H             // prevent multiple definitions if this 
#define _REDSPACE_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "Planet.h"
#include "Missile.h"
#include "PlayerPlanet.h"
#include "Controls.h"
#include "SmokeParticle.h"
#include"Shot.h"
#include <string>
using std::string;
#include <ctime>;


//=============================================================================
// Create game class
//=============================================================================
class RedSpace : public Game
{
private:
    // variables
	TextureManager backgroundTex;   // nebula texture
    TextureManager planetTexture;   // planet texture
	TextureManager marsTex;
	TextureManager earthTex;
    TextureManager misTexture;     // missile texture
	TextureManager explosionTex;
	TextureManager cursorTex;
	TextureManager smokeTex;
	TextureManager shotTex;
	TextureManager barTex;
	Image marsBar;
	Image earthBar;
	Planet  sun;         
	PlayerPlanet mars;
	PlayerPlanet earth;
	Missile missile;
	Image   background;         // backdrop image
	Missile mc[MISSILEMAX];
	SmokeParticle particles[PARTICLEMAX];
	Explosion exp[EXPMAX];
	Shot shots[SHOTMAX];
	int numActiveMissles;
	int numActiveParticles;
	int numActiveShot;
	int misStorage;
	int partStorage;
	int shotStorage;
	Controls P1Controls, P2Controls;
	TextDX earthText;
	TextDX marsText;
	TextDX NewsText;
	float NewsLocation;
	int currentNewsIndex;
	
public:
    // Constructor
    RedSpace();

    // Destructor
    virtual ~RedSpace();

    // Initialize the game
    void initialize(HWND hwnd);
    void update();      // must override pure virtual from Game
    void ai();          // "
    void collisions();  // "
    void render();      // "
    void releaseAll();
    void resetAll();

	void spawnMissle(D3DXVECTOR2 location, D3DXVECTOR2 velocity, COLOR_ARGB color);
	void spawnSmokeParticle(D3DXVECTOR2 location);
	void spawnShot(D3DXVECTOR2 location, D3DXVECTOR2 velocity);

	void updateNews();




};

#endif
