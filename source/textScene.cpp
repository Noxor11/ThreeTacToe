#include "textScene.h"


C2D_TextBuf g_staticBuf;
std::array<C2D_Text, 4> g_staticText;
std::array<C2D_Text, 10> numberText;
C2D_Font font;

#define PLAYER1_TEXT_Y_POS HEIGHT_CENTER + 20
#define PLAYER2_TEXT_Y_POS PLAYER1_TEXT_Y_POS + 40


namespace textScene{

	void initTextScene(void)
	{
		g_staticBuf = C2D_TextBufNew(4096); // support up to 4096 glyphs in the buffer
		font = C2D_FontLoad("romfs:/gfx/Akaya.bcfnt");


		// Uses other loaded font
		C2D_TextFontParse(&g_staticText[0], font, g_staticBuf, "Local Game");
		C2D_TextFontParse(&g_staticText[1], font, g_staticBuf, "Online Game");
		C2D_TextFontParse(&g_staticText[2], font, g_staticBuf, "Player 1 Score:");
		C2D_TextFontParse(&g_staticText[3], font, g_staticBuf, "Player 2 Score:");


		//	Numbers for score display
		C2D_TextFontParse(&numberText[0], font, g_staticBuf, "0");
		C2D_TextFontParse(&numberText[1], font, g_staticBuf, "1");
		C2D_TextFontParse(&numberText[2], font, g_staticBuf, "2");
		C2D_TextFontParse(&numberText[3], font, g_staticBuf, "3");
		C2D_TextFontParse(&numberText[4], font, g_staticBuf, "4");
		C2D_TextFontParse(&numberText[5], font, g_staticBuf, "5");
		C2D_TextFontParse(&numberText[6], font, g_staticBuf, "6");
		C2D_TextFontParse(&numberText[7], font, g_staticBuf, "7");
		C2D_TextFontParse(&numberText[8], font, g_staticBuf, "8");
		C2D_TextFontParse(&numberText[9], font, g_staticBuf, "9");


		// Optimize the text strings
		for(C2D_Text txt: g_staticText){
			C2D_TextOptimize(&txt);
		}


		for(C2D_Text txt: numberText){
			C2D_TextOptimize(&txt);
		}
	}

	void drawMenu(float size)
	{
		// Draw static text strings
		C2D_DrawText(&g_staticText[0], 0, 100, HEIGHT_CENTER - 30, 0.5f, size, size);
		C2D_DrawText(&g_staticText[1], 0, 100, HEIGHT_CENTER, 0.5f, size, size);

	}


	void drawScore(float size, std::string score1Arr, std::string score2Arr)
	{
		
		// First Player
		C2D_DrawText(&g_staticText[2], 0, 50, PLAYER1_TEXT_Y_POS, 0.5f, size, size);

		//	For every char in the score, convert to int and display it
		for(int i = 0, xPos = 240; i < (int) score1Arr.length(); i++, xPos += 20){
			int p1 = score1Arr[i] - '0';
				C2D_DrawText(&numberText[p1], 0, xPos, PLAYER1_TEXT_Y_POS, 0.5f, size, size);

		}

		
		// Second Player
		C2D_DrawText(&g_staticText[3], 0, 50, PLAYER2_TEXT_Y_POS, 0.5f, size, size);

		//	For every char in the score, convert to int and display it
		for (int i = 0, xPos = 240; i < (int)score2Arr.length(); i++, xPos += 20) {
			int p2 = score2Arr[i] - '0';
			C2D_DrawText(&numberText[p2], 0, xPos, PLAYER2_TEXT_Y_POS, 0.5f, size, size);

		}




	}


	void exitTextScene(void)
	{
		// Delete the text buffers
		C2D_TextBufDelete(g_staticBuf);
		C2D_FontFree(font);

	}
}