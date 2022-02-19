#pragma once
#include "gameObjects.h"



void initScene();

void stopScene(C2D_SpriteSheet* spriteSheet);

void renderScene(C3D_RenderTarget* scene);


void draw(Object* object);
void drawPieceTop(Object* object);
void drawPieceBottom(Object* object);
