#include "scene.h"

#define GAME_TIME 60

namespace gameScene{


	void initScene() {

		romfsInit();
		cfguInit(); // Allow C2D_FontLoadSystem to work
		gfxInitDefault();
		C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
		C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
		C2D_Prepare();


	}

	void stopScene(C2D_SpriteSheet* spriteSheet) {
		C2D_Fini();
		C3D_Fini();
		gfxExit();
		romfsExit();

		// Delete graphics
		C2D_SpriteSheetFree(*spriteSheet);

		
	}


	void renderScene(C3D_RenderTarget* screen) {


		C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
		C2D_TargetClear(screen, C2D_Color32(0x68, 0xB0, 0xD8, 0xFF));
		C2D_SceneBegin(screen);
	}

	void draw(Object* object) {
		C2D_DrawSprite(object->getSprite());

	}



}

