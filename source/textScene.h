#pragma once
#include "scene.h"
#include <charconv>


#define PLAYER1_TEXT_Y_POS HEIGHT_CENTER -100
#define PLAYER2_TEXT_Y_POS PLAYER1_TEXT_Y_POS + 40

namespace textScene{
    
    
    void initTextScene(void);
    void drawOnlineLocalMenu(float size);
    void drawClassicRushMenu(float size);

    void drawTime(int seconds, float size);

    void drawScore(float size, std::string score1Arr, std::string score2Arr);

    void exitTextScene(void);

    
}