#pragma once
#include "scene.h"

namespace textScene{
    
    void initTextScene(void);
    void drawMenu(float size);

    void drawScore(float size, std::string score1Arr, std::string score2Arr);

    void exitTextScene(void);
}