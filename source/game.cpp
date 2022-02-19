#include "game.h"
#include "scene.h"
#include "textScene.h"
#include <iostream>


float textSize = 1.0f;





void Game::playerMove(u32 kDown ) {
	if (playerHasNotChosen) {
		if (kDown & KEY_UP && yTilesAway < 1) {
			pieceOnPlay->moveYBy(66);
			placingPosition -= 3;
			yTilesAway++;
		}

		if (kDown & KEY_DOWN && yTilesAway > -1) {
			pieceOnPlay->moveYBy(-66);
			placingPosition += 3;
			yTilesAway--;
		}

		if (kDown & KEY_RIGHT && xTilesAway < 1) {
			pieceOnPlay->moveXBy(66);
			placingPosition++;
			xTilesAway++;
		}

		if (kDown & KEY_LEFT && xTilesAway > -1) {
			pieceOnPlay->moveXBy(-66);
			placingPosition--;
			xTilesAway--;
		}

		if (kDown & KEY_A) {	//	Place if there's not another piece below
			if (placePiece()) {
				if (isPlayer1Turn)
					placedPos[placingPosition] = 1;
				else
					placedPos[placingPosition] = 2;
					
				playerHasNotChosen = 0;
			}
		}
	}
	else {
		nextTurn();
		xTilesAway = 0;
		yTilesAway = 0;
		playerHasNotChosen = 1;
	}
}


bool Game::isPlaceFree() {
	for (int i = 0; i < placedPiecesCnt; i++)
		if(pieceOnPlay->hasSamePosAs(placedPieces[i]))
			return 0;

	return 1;
}




void Game::drawPlacedPieces() {
	for (int i = 0; i < placedPiecesCnt; i++)
		draw(placedPieces[i]);
}

void Game::drawPieceOnPlay() {
	draw(pieceOnPlay);
}


void Game::showScore() {
	drawScore(textSize, *scoreP1Arr, *scoreP2Arr);
}



bool Game::placePiece() {

	if (isPlaceFree()) {

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
		
		return 1;
	}
	else {

		//	TODO: Do something
		return 0;
	}
}

void Game::nextTurn() {
	isPlayer1Turn = !(isPlayer1Turn);
	placingPosition = 4;
	turnsPlayed++;
}

bool Game::isTie() {
	if (turnsPlayed == 9)
		return TIE;
	return 0;
}


void Game::drawGameMenu() {
	drawMenu(textSize);
}

void Game::chooseMode() {
	renderScene(bottomScreen);
	
	
	if (gameMode < 1) {
		if (kDown & KEY_UP) {

			arrow->setPos(70, HEIGHT_CENTER - 15);
			gameMode = -LOCAL_GAME; // not selected
		}

		if (kDown & KEY_DOWN) {
			arrow->setPos(70, HEIGHT_CENTER + 15);
			gameMode = -ONLINE_GAME; //	not selected
		}

		if (kDown & KEY_A) {
			gameMode *= -1;	//	select game by making it positive
		}

		draw(arrow);
		drawMenu(textSize);

		

	}
	else if (gameMode == LOCAL_GAME) {
		showScore();
		renderScene(topScreen);
		startLocalGame(kDown);

	}

}

void Game::startLocalGame(u32 kDown) {

	draw(grid);
	drawPlacedPieces();

	if (!gameOver() ) {
		drawPieceOnPlay();
		playerMove(kDown);

	}
	else {
		if (isTie()) {
			printf("\x1b[12;7HLa vieja won!");
			
		}
		else {

			printf("\x1b[12;7HPlayer %d Won!", gameOver());


		}


		
		if(countDownNewRound-- < 0){

			if (gameOver() == 1)
				addPointsTo(scoreP1, scoreP1Arr);
			else if(gameOver() == 2)
				addPointsTo(scoreP2, scoreP2Arr);

			nextRound();
		}

	}
}

void Game::changeFirstPiece() {
	Object* tmp = gamePieces[0];


	//	Exchange moving Pieces
	gamePieces[0] = gamePieces[2];
	gamePieces[2] = tmp;

	//	Exchange static Pieces
	tmp = gamePieces[1];

	gamePieces[1] = gamePieces[3];
	gamePieces[3] = tmp;


}

void Game::resetMovingPiecePos() {
	xTilesAway = 0;
	yTilesAway = 0;
}


void Game::nextRound() {
	for (int i = 0; i < 9; i++)
		placedPos[i] = 0;

	for (int i = 0; i < 0; i++)
		placedPieces[i] = 0;


	isPlayer1First = !(isPlayer1First);
	isPlayer1Turn = isPlayer1First;
	changeFirstPiece();
	resetMovingPiecePos();
	placedPiecesCnt = 0;
	gPiecesIndex = 0;
	pieceOnPlay = gamePieces[0];
	turnsPlayed = 0;
	playerHasNotChosen = 1;
	placingPosition = 4;

	

	countDownNewRound = COUNTDOWN;


}

int Game::gameOver() {


	//	Horizontal Check
	if (placedPos[0] != 0 && placedPos[0] == placedPos[1] && placedPos[0] == placedPos[2])
		return placedPos[0];
	
	if (placedPos[3] != 0 && placedPos[3] == placedPos[4] && placedPos[3] == placedPos[5])
		return placedPos[3];

	if (placedPos[6] != 0 && placedPos[6] == placedPos[7] && placedPos[6] == placedPos[8])
		return placedPos[6];

	//	Vertical Check
	
	if (placedPos[0] != 0 && placedPos[0] == placedPos[3] && placedPos[0] == placedPos[6])
		return placedPos[0];

	if (placedPos[1] != 0 && placedPos[1] == placedPos[4] && placedPos[1] == placedPos[7])
		return placedPos[1];

	if (placedPos[2] != 0 && placedPos[2] == placedPos[5] && placedPos[2] == placedPos[8])
		return placedPos[2];

	//	Diagonal Check

	if (placedPos[0] != 0 && placedPos[0] == placedPos[4] && placedPos[0] == placedPos[8])
		return placedPos[0];

	if (placedPos[2] != 0 && placedPos[2] == placedPos[4] && placedPos[2] == placedPos[6])
		return placedPos[2];

	return isTie();

}




void Game::setScreens(C3D_RenderTarget* tScreen, C3D_RenderTarget* botScreen) {
	topScreen = tScreen;
	bottomScreen = botScreen;
}


void Game::userInput(C2D_SpriteSheet* spriteSheet) {
	// Respond to user input
	hidScanInput();

	kDown = hidKeysDown();
	if (kDown & KEY_START) {
		exitTextScene();
		cfguExit();


		// De-init libs and sprites
		stopScene(spriteSheet);
		exit(0);	// break in order to return to hbmenu
	}

}

void Game::addPointsTo(int& playerScore, std::string* scoreArr ) {
	playerScore++;	
	*scoreArr = *(new std::string(std::to_string(playerScore)));
	
}



void Game::playAgain() {
	
}


Game::Game(Object* _grid, Object* p1Piece, Object* p1SelectedPiece, Object* p2Piece, Object* p2SelectedPiece, Object* _arrow) {
	gamePieces[0] = p1Piece;
	gamePieces[1] = p1SelectedPiece;
	gamePieces[2] = p2Piece;
	gamePieces[3] = p2SelectedPiece;




	isPlayer1First = 1;
	isPlayer1Turn = 1;
	placedPiecesCnt = 0;
	gPiecesIndex = 0;
	placingPosition = 4;
	pieceOnPlay = gamePieces[0];
	grid = _grid;
	arrow = _arrow;
}

Player::Player(Object* pi) {
	piece = pi;
}

Player::Player() {
	
}
