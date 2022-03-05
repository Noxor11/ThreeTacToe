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
	Object* bgAvailable;
	Object* bgNotAvailable;
	Object* bg;


	C2D_ImageTint* red;

	std::string* scoreP1Arr;
	std::string* scoreP2Arr;



	int gPiecesIndex;

	int placedPiecesCnt;

	

	Object* pieceOnPlay;


	C3D_RenderTarget* topScreen;
	C3D_RenderTarget* bottomScreen;

	void changeFirstPiece();


public:
	void setScreens(C3D_RenderTarget* tScreen, C3D_RenderTarget* botScreen);
	void prepareNextRound();
	void drawPieceOnPlay();
	void drawPlacedPieces();
	void drawArrow();
	void drawGrid();
	void drawScore();
	void drawMenu();
	void drawTime(int seconds);
	void selectMode(int mode);
	void initScore();
	void setScoreP1(int scoreP1);
	void setScoreP2(int scoreP2);

	void renderTopScreen();
	void renderBotScreen();
	void placePiece();

	void moveCursorUp();
	void moveCursorDown();
	void moveCursorLeft();
	void moveCursorRight();
	void setPieceBackground(int background);



	GameGraphics(Object* grid, Object* p1Piece, Object* p1SelectedPiece, Object* p2Piece, Object* p2SelectedPiece, Object* arrow, Object* available, Object* not_available);
};