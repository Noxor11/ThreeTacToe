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

static C2D_SpriteSheet spriteSheet;
static Object* sprites = new Object[MAX_SPRITES];






//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
	//---------------------------------------------------------------------------------


	gameScene::initScene();
	textScene::initTextScene();
	
	

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bot = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);


	// Load graphics
	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!spriteSheet) svcBreak(USERBREAK_PANIC);


	// Create Sprites from sprite sheet
	Object* grid		= new Object(sprites, &spriteSheet, 0);
	Object* x			= new Object(sprites, &spriteSheet, 1);
	Object* xRed		= new Object(sprites, &spriteSheet, 2);
	Object* o			= new Object(sprites, &spriteSheet, 3);
	Object* oBlue		= new Object(sprites, &spriteSheet, 4);
	Object* messageBox	= new Object(sprites, &spriteSheet, 5);
	

	Object* arrow		= new Object(sprites, &spriteSheet, 6, -150, 0);
	arrow->setPos(70, HEIGHT_CENTER - 15);

	
	GameGraphics* gfx = new GameGraphics(grid, x, xRed, o, oBlue, arrow);

	

	Game gm(gfx);

	gm.setScreens(top, bot);






	// Main loop
	while (aptMainLoop()){

		gm.userInput(&spriteSheet);
		gm.chooseMode();

		C3D_FrameEnd(0);
	}

	// Deinitialize the scene
	textScene::exitTextScene();
	cfguExit();


	// De-init libs and sprites
	gameScene::stopScene(&spriteSheet);

	return 0;
}