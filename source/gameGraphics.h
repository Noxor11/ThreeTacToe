#pragma once
#include "gameObjects.h"
#include "textScene.h"
#include "scene.h"

#define BACKGROUND_AVAILABLE 1
#define BACKGROUND_OCCUPIED	 2


class GameGraphics {
private:

	Object* grid;
	Object* gamePieces[4] = {};



	Object* placedPieces[9] = {};

	Object* arrow;
	C2D_Image bgAvailable;
	C2D_Image bgNotAvailable;
	Object* bg;

	C2D_Image currentPieceImage;


	C2D_ImageTint* red;

	std::string* scoreP1Arr;
	std::string* scoreP2Arr;



	int gPiecesIndex;

	int placedPiecesCnt;

	bool wasXFirst = true;
	

	Object* pieceOnPlay;
	Object staticPieceOnPlay;


	C3D_RenderTarget* topScreen;
	C3D_RenderTarget* bottomScreen;

	void changeFirstPiece();


public:

	C2D_SpriteSheet spriteSheet;
	void setScreens(C3D_RenderTarget* tScreen, C3D_RenderTarget* botScreen);
	void prepareNextRound();
	void drawPieceOnPlay();
	void drawPlacedPieces();
	void drawArrow();
	void drawGrid();
	void drawScore();
	void drawOnlineLocalMenu();
	void drawClassicRushMenu();
	void drawTime(int seconds);
	void selectMode(int mode);
	void initScore();
	void setScoreP1(int scoreP1);
	void setScoreP2(int scoreP2);

	void renderTopScreen();
	void renderBotScreen();
	void placePiece(int placing_position);
	void changePieceOnPlay();

	void moveCursorUp();
	void moveCursorDown();
	void moveCursorLeft();
	void moveCursorRight();
	void moveCursorToPlace(int index);
	void setPieceBackground(int index, int background);

	void showPieceOnPlayTopScreen();



	Object* getGrid();


	GameGraphics();
};