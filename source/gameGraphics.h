#pragma once
#include "gameObjects.h"
#include "textScene.h"
#include "scene.h"

class GameGraphics {
private:
	Object* grid;
	Object* gamePieces[4] = {};
	Object* placedPieces[9] = {};
	Object* arrow;


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
	void drawMenu(float size);
	void selectMode(int mode);

	void renderTopScreen();
	void renderBotScreen();
	void placePiece();

	void moveCursorUp();
	void moveCursorDown();
	void moveCursorLeft();
	void moveCursorRight();


	GameGraphics(Object* grid, Object* p1Piece, Object* p1SelectedPiece, Object* p2Piece, Object* p2SelectedPiece, Object* arrow);
};