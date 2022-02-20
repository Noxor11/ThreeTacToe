#pragma once

#include <citro2d.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <citro2d.h>
#include <3ds.h>
#include <string>

#define MAX_SPRITES			768
#define SCREEN_WIDTH		400
#define SCREEN_HEIGHT		240
#define FLOOR				224
#define BACKGROUND_SIZE		512
#define WIDTH_CENTER		SCREEN_WIDTH  / 2
#define HEIGHT_CENTER		SCREEN_HEIGHT / 2


class Object {
	C2D_Sprite spr;

public:
	float px();
	float py();
	void setX(float newPosition);
	void setY(float newPosition);
	void setPos(float xPosition, float yPosition);
	void setPos(Object* objectToGetPositionFrom);
	bool hasSamePosAs(Object* objectToGwtPositionFrom);
	void moveXBy(float increment);
	void moveYBy(float increment);
	void moveBy(float xIncrement, float yIncrement);


	C2D_Sprite* getSprite();
	void initSpriteCenter(C2D_SpriteSheet* spriteSheet, int index);
	void initSpriteBottomCenter(C2D_SpriteSheet* spriteSheet, int index);
	void initSpriteAt(C2D_SpriteSheet* spriteSheet, int index, float xPosition, float yPosition);

	Object(Object* sprite, C2D_SpriteSheet* spriteSheet, int index);
	Object(Object* sprite, C2D_SpriteSheet* spriteSheet, int index, float xPosition, float yPosition);
	Object();

};
