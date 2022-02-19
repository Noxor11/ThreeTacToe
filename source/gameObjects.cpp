#include "gameObjects.h"



float Object::px(){
	return spr.params.pos.x;
}

float Object::py() {
	return spr.params.pos.y;
}

void Object::setX(float newPosition) {
	spr.params.pos.x = newPosition ;
}

void Object::setY(float newPosition) {
	spr.params.pos.y = newPosition;
}

void Object::setPos(float xPosition, float yPosition) {
	spr.params.pos.x = xPosition;
	spr.params.pos.y = yPosition;
}

void Object::setPos(Object* objectToGetPositionFrom) {
	spr.params.pos = objectToGetPositionFrom->spr.params.pos;

}

bool Object::hasSamePosAs(Object* objectToGwtPositionFrom) {
	return spr.params.pos.x == objectToGwtPositionFrom->spr.params.pos.x &&
		   spr.params.pos.y == objectToGwtPositionFrom->spr.params.pos.y;
}

C2D_Sprite* Object::getSprite() {
	return &spr;
}



void Object::moveXBy(float increment) {
	spr.params.pos.x += increment;
}

void Object::moveYBy(float increment) {
	spr.params.pos.y -= increment;
}

void Object::moveBy(float xIncrement, float yIncrement) {
	setX(spr.params.pos.x + xIncrement);
	setY(spr.params.pos.y - yIncrement);
}


Object::Object(Object* sprite, C2D_SpriteSheet* spriteSheet, int index) {
	spr = sprite[index].spr;
	initSpriteCenter(spriteSheet, index);

}

Object::Object(Object* sprite, C2D_SpriteSheet* spriteSheet, int index, float xPosition, float yPosition) {
	spr = sprite[index].spr;
	initSpriteAt(spriteSheet, index, xPosition, yPosition);
}

Object::Object() {
}

void Object::initSpriteAt(C2D_SpriteSheet* spriteSheet, int index, float xPosition, float yPosition) {
	C2D_SpriteFromSheet(&spr, *spriteSheet, index);
	C2D_SpriteSetCenter(&spr, 0.5f, 0.5f);
	C2D_SpriteSetPos(&spr, xPosition + WIDTH_CENTER, yPosition * -1 + HEIGHT_CENTER);
}

void Object::initSpriteCenter(C2D_SpriteSheet* spriteSheet, int index) {
	initSpriteAt(spriteSheet, index, 0, 0);
}


void Object::initSpriteBottomCenter(C2D_SpriteSheet* spriteSheet, int index) {
	initSpriteAt(spriteSheet, index, 0, HEIGHT_CENTER);
}

