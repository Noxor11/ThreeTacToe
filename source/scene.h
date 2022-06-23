#pragma once
#include "gameObjects.h"


namespace gameScene{
    void initScene();

    void stopScene(C2D_SpriteSheet* spriteSheet);

    void renderScene(C3D_RenderTarget* screen);

    void draw(Object* object);

}