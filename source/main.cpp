#include <citro2d.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>


#include "scene.h"
#include "game.h"
#include "textScene.h"

#define MAX_SPRITES   768
#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240







//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
	//---------------------------------------------------------------------------------


	gameScene::initScene();
	textScene::initTextScene();
	
	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bot = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

	
	GameGraphics* gfx = new GameGraphics();

	

	Game gm(gfx);

	gm.setScreens(top, bot);





	// Main loop
	while (aptMainLoop()){

		

		gm.userInput();
		gm.chooseMode();

		C3D_FrameEnd(0);
		

		
	}

	

	gm.deInit();
	


	return 0;
}