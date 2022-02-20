#include "gameGraphics.h"

#define LOCAL_GAME	1
#define ONLINE_GAME 2


void GameGraphics::setScreens(C3D_RenderTarget* tScreen, C3D_RenderTarget* botScreen) {
	topScreen = tScreen;
	bottomScreen = botScreen;
}



void GameGraphics::prepareNextRound() {
	for (int i = 0; i < placedPiecesCnt; i++)
		placedPieces[i] = nullptr;

	placedPiecesCnt = 0;
	changeFirstPiece();
	gPiecesIndex = 0;
	pieceOnPlay = gamePieces[0];
}


void GameGraphics::drawPieceOnPlay() {
	gameScene::draw(pieceOnPlay);
}


void GameGraphics::drawPlacedPieces() {
	for (int i = 0; i < placedPiecesCnt; i++)
		gameScene::draw(placedPieces[i]);
}

void GameGraphics::drawGrid() {
	gameScene::draw(grid);
}

void GameGraphics::drawArrow() {
	gameScene::draw(arrow);
}

void GameGraphics::drawMenu(float size){
	textScene::drawMenu(size);
}

void GameGraphics::renderTopScreen() {
	gameScene::renderScene(topScreen);
}

void GameGraphics::renderBotScreen() {
	gameScene::renderScene(bottomScreen);
}

void GameGraphics::selectMode(int mode) {
	switch (mode) {
	case LOCAL_GAME:
		arrow->setPos(70, HEIGHT_CENTER - 15);
		break;
	case ONLINE_GAME:
		arrow->setPos(70, HEIGHT_CENTER + 15);
		break;
	}

}

void GameGraphics::moveCursorUp() {
	pieceOnPlay->moveYBy(66);
}
void GameGraphics::moveCursorDown() {
	pieceOnPlay->moveYBy(-66);
}
void GameGraphics::moveCursorLeft() {
	pieceOnPlay->moveXBy(-66);
}
void GameGraphics::moveCursorRight() {
	pieceOnPlay->moveXBy(66);
}

void GameGraphics::placePiece() {
	gamePieces[gPiecesIndex + 1]->setPos(WIDTH_CENTER, HEIGHT_CENTER);

	Object* tmp = new Object(*gamePieces[gPiecesIndex + 1]);
	tmp->setPos(pieceOnPlay);

	placedPieces[placedPiecesCnt] = tmp;
	placedPiecesCnt++;

	if (gPiecesIndex == 0) {
		gPiecesIndex = 2;
	}
	else {
		gPiecesIndex = 0;
	}

	pieceOnPlay->setPos(WIDTH_CENTER, HEIGHT_CENTER);
	pieceOnPlay = gamePieces[gPiecesIndex];
}

void GameGraphics::changeFirstPiece() {
	Object* tmp = gamePieces[0];


	//	Exchange moving Pieces
	gamePieces[0] = gamePieces[2];
	gamePieces[2] = tmp;

	//	Exchange static Pieces
	tmp = gamePieces[1];

	gamePieces[1] = gamePieces[3];
	gamePieces[3] = tmp;


}








GameGraphics::GameGraphics(Object* _grid, Object* p1Piece, Object* p1SelectedPiece, Object* p2Piece, Object* p2SelectedPiece, Object* _arrow) {
	gamePieces[0] = p1Piece;
	gamePieces[1] = p1SelectedPiece;
	gamePieces[2] = p2Piece;
	gamePieces[3] = p2SelectedPiece;

	gPiecesIndex = 0;
	placedPiecesCnt = 0;
	pieceOnPlay = gamePieces[0];
	grid = _grid;
	arrow = _arrow;

}