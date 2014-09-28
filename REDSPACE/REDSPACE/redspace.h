// Programming 2D Games
// Copyright (c) 2011 by: 
// Charles Kelly
// Chapter 4 spacewar.h v1.0

#ifndef _REDSPACE_H             // prevent multiple definitions if this 
#define _REDSPACE_H             // ..file is included in more than one place
#define WIN32_LEAN_AND_MEAN

#include "game.h"
#include "Planet.h"


//=============================================================================
// Create game class
//=============================================================================
class RedSpace : public Game
{
private:
    // variables
	TextureManager backgroundTex;   // nebula texture
    TextureManager planetTexture;   // planet texture
    TextureManager shipTexture;     // ship texture
	Planet  planet;         // the planet
	Image   background;         // backdrop image
	//Image* list[6];


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
};

#endif