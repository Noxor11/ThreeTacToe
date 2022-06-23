#include "textScene.h"

C2D_TextBuf g_staticBuf;
std::array<C2D_Text, 8> g_staticText;
std::array<C2D_Text, 10> scoreNumberText;
C2D_Font font;





namespace textScene{

	void initTextScene(void)
	{
		g_staticBuf = C2D_TextBufNew(4096); // support up to 4096 glyphs in the buffer
		font = C2D_FontLoad("romfs:/gfx/Akaya.bcfnt");


		//	------------------------------Set strings---------------------------------
		C2D_TextFontParse(&g_staticText[0], font, g_staticBuf, "Local Game");
		C2D_TextFontParse(&g_staticText[1], font, g_staticBuf, "Online Game");
		C2D_TextFontParse(&g_staticText[2], font, g_staticBuf, "Player 1");
		C2D_TextFontParse(&g_staticText[3], font, g_staticBuf, "Player 2");
		C2D_TextFontParse(&g_staticText[4], font, g_staticBuf, "Score:");

		C2D_TextFontParse(&g_staticText[5], font, g_staticBuf, "Player 2 Score:");

		C2D_TextFontParse(&g_staticText[6], font, g_staticBuf, "Classic Mode");
		C2D_TextFontParse(&g_staticText[7], font, g_staticBuf, "Rush    Mode");




		//	Numbers for score display
		for (int i = 0; i < (int) scoreNumberText.size(); i++){
			C2D_TextFontParse(&scoreNumberText[i], font, g_staticBuf, std::to_string(i).c_str());
		}
		//	---------------------------------------------------------------------------


		// --------------Optimize text strings-------------
		for(C2D_Text txt: g_staticText){
			C2D_TextOptimize(&txt);
		}


		for(C2D_Text txt: scoreNumberText){
			C2D_TextOptimize(&txt);
		}
		// ----------------------------------------------------
	}


	void drawOnlineLocalMenu(float size)
	{
		// Draw static text strings
		C2D_DrawText(&g_staticText[0], 0, 100, HEIGHT_CENTER - 30, 0.5f, size, size);
		C2D_DrawText(&g_staticText[1], 0, 100, HEIGHT_CENTER, 0.5f, size, size);

	}

	void drawClassicRushMenu(float size){
		
		// Draw static text strings
		C2D_DrawText(&g_staticText[6], 0, 100, HEIGHT_CENTER - 30, 0.5f, size, size);
		C2D_DrawText(&g_staticText[7], 0, 100, HEIGHT_CENTER, 0.5f, size, size);

	}


	void drawScore(float size, std::string score1Arr, std::string score2Arr)
	{

		// First Player
		C2D_DrawText(&g_staticText[2], 0, 50, PLAYER1_TEXT_Y_POS, 0.5f, size, size);
		C2D_DrawText(&g_staticText[4], 0, 30 + g_staticText[2].width * size, PLAYER1_TEXT_Y_POS, 0.5f, size, size);


		//	For every char in the score, convert to int and display it
		for(int i = 0, xPos = 250; i < (int) score1Arr.length(); i++, xPos += 20){
			int p1 = score1Arr[i] - '0';
				C2D_DrawText(&scoreNumberText[p1], 0, xPos, PLAYER1_TEXT_Y_POS, 0.5f, size, size);

		}

		
		// Second Player
		C2D_DrawText(&g_staticText[3], 0, 50, PLAYER2_TEXT_Y_POS, 0.5f, size, size);
		C2D_DrawText(&g_staticText[4], 0, 30 + g_staticText[2].width * size, PLAYER2_TEXT_Y_POS, 0.5f, size, size);

		//	For every char in the score, convert to int and display it
		for (int i = 0, xPos = 250; i < (int)score2Arr.length(); i++, xPos += 20) {
			int p2 = score2Arr[i] - '0';
			C2D_DrawText(&scoreNumberText[p2], 0, xPos, PLAYER2_TEXT_Y_POS, 0.5f, size, size);

		}
	}

	void drawTime(int seconds, float size){
				//Print current time

		std::string secondsStr = std::to_string(seconds);

		//	For every char in minutes, convert to int and display it
		for(int i = 0, xPos = 0; i < (int) secondsStr.length(); i++, xPos += 20){
			int p1 = secondsStr[i] - '0';
				C2D_DrawText(&scoreNumberText[p1], 0, xPos, SCREEN_HEIGHT - 40, 0.5f, size, size);

		}



	}


	void exitTextScene(void)
	{
		// Delete the text buffers
		C2D_TextBufDelete(g_staticBuf);
		C2D_FontFree(font);

	}
}