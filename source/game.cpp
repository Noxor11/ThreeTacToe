#include "game.h"
#include "scene.h"
#include <iostream>


#define PLAYER1	1
#define PLAYER2	2
float textSize = 1.0f;





void Game::playerMove(u32 kDown ) {
	if (playerHasNotChosen) {
		if (kDown & KEY_UP && yTilesAway < 1) {
			
			moveCursorUp();
			
		}

		if (kDown & KEY_DOWN && yTilesAway > -1) {
			moveCursorDown();
			
		}

		if (kDown & KEY_RIGHT && xTilesAway < 1) {
			moveCursorRight();
			
		}

		if (kDown & KEY_LEFT && xTilesAway > -1) {
			moveCursorLeft();
			
		}

		if (kDown & KEY_A) {	//	Place if there's not another piece below
			if (placePiece()) {

				//	Piece to place belongs to...
				if (isPlayer1Turn)
					placedPos[placingPosition] = PLAYER1;
				else
					placedPos[placingPosition] = PLAYER2;
					
				playerHasNotChosen = 0;
			}
		}
	}
	else {
		nextTurn();
	}
}


bool Game::isPlaceFree() {
	//	Return wether that pos has a score
	return placedPos[placingPosition] == 0;
}




void Game::drawPlacedPieces() {
	gfx->drawPlacedPieces();
}

void Game::drawPieceOnPlay() {
	gfx->drawPieceOnPlay();
}


void Game::showScore() {
	textScene::drawScore(textSize, *scoreP1Arr, *scoreP2Arr);
}

void Game::resetMovingPiecePos() {
	xTilesAway = 0;
	yTilesAway = 0;

}


bool Game::placePiece() {

	if (isPlaceFree()) {

		
		placedPiecesCnt++;

		gfx->placePiece();

		
		
		return 1;
	}
	else {

		//	TODO: Do something
		return 0;
	}
}

void Game::nextTurn() {
	resetMovingPiecePos();

	isPlayer1Turn = !(isPlayer1Turn);
	placingPosition = 4;
	playerHasNotChosen = 1;
	turnsPlayed++;
}

bool Game::isTie() {
	if (turnsPlayed == 9)
		return TIE;
	return 0;
}

void Game::moveCursorUp() {
	gfx->moveCursorUp();
	placingPosition -= 3;
	yTilesAway++;
}
void Game::moveCursorDown() {
	gfx->moveCursorDown();
	placingPosition += 3;
	yTilesAway--;
}
void Game::moveCursorRight() {
	gfx->moveCursorRight();
	placingPosition++;
	xTilesAway++;
}
void Game::moveCursorLeft() {
	gfx->moveCursorLeft();
	placingPosition--;
	xTilesAway--;
}


void Game::drawGameMenu() {
	gfx->drawMenu(textSize);
}

void Game::chooseMode() {
	gfx->renderBotScreen();
	
	
	if (gameMode < 1) {
		if (kDown & KEY_UP) {
			selectMode(LOCAL_GAME);
		}

		if (kDown & KEY_DOWN) {
			selectMode(ONLINE_GAME);
		}

		if (kDown & KEY_A) {
			confirmSelect();
		}

		gfx->drawArrow();
		gfx->drawMenu(textSize);

		

	}
	else if (gameMode == LOCAL_GAME) {
		showScore();
		gfx->renderTopScreen();
		startLocalGame(kDown);

	}

}

void Game::startLocalGame(u32 kDown) {

	gfx->drawGrid();
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
				addPointsTo(PLAYER1);

			else if(gameOver() == 2)
				addPointsTo(PLAYER2);

			nextRound();
		}

	}
}

void Game::selectMode(int mode) {
	gfx->selectMode(mode);
	gameMode = -mode;

}

void Game::confirmSelect() {
	gameMode *= -1;	//	select game by making it positive
}




void Game::nextRound() {

	resetMovingPiecePos();

	//	Reset pieces in board
	for (int i = 0; i < 9; i++)
		placedPos[i] = 0;



	isPlayer1First = !(isPlayer1First);
	isPlayer1Turn = isPlayer1First;
	placedPiecesCnt = 0;
	turnsPlayed = 0;
	playerHasNotChosen = 1;
	placingPosition = 4;

	countDownNewRound = COUNTDOWN;
	gfx->prepareNextRound();
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


	//	If no player has gotten three on line, return wether it's a draw or not 
	return isTie();

}







void Game::userInput(C2D_SpriteSheet* spriteSheet){
	// Respond to user input
	hidScanInput();

	kDown = hidKeysDown();
	if (kDown & KEY_START) {
		textScene::exitTextScene();
		cfguExit();


		// De-init libs and sprites
		gameScene::stopScene(spriteSheet);
		exit(0);	// break in order to return to hbmenu
	}

}

void Game::addPointsTo(int Player){
	if(Player == PLAYER1){
		scoreP1++;	
		scoreP1Arr = new std::string(std::to_string(scoreP1));
	}
	else if(Player == PLAYER2){
		scoreP2++;	
		scoreP2Arr = new std::string(std::to_string(scoreP2));
	}
	
}

void Game::setScreens(C3D_RenderTarget* top, C3D_RenderTarget* bot) {
	gfx->setScreens(top, bot);
}



void Game::playAgain() {
	
}




Game::Game(GameGraphics* gfx_) {

	this->gfx= gfx_;
	scoreP1Arr = new std::string("0");
	scoreP2Arr = new std::string("0");

	scoreP1 = 0;
	scoreP2 = 0;

	playerHasNotChosen = 1;
	turnsPlayed = 0;
	isPlayer1First = 1;
	isPlayer1Turn = 1;
	placedPiecesCnt = 0;
	placingPosition = 4;

	resetMovingPiecePos();
}

