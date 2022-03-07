#include "game.h"
#include "scene.h"
#include <iostream>


#define PLAYER1		1
#define PLAYER2	   -1
#define SAME_PIECE	3

#define PLACED		1
#define	NOT_PLACED	0









void Game::playerMove(u32 kDown ) {

	if (playerHasNotChosen) {

		checkForMovement();
	}
	
	else 
		nextTurn();
}


bool Game::isPlaceFree() {
	//	Return wether that pos has a score
	return placedPos[placingPosition] == 0;
}

void Game::checkForMovement(){
	if (kDown & KEY_UP && yTilesAway < 1) 
		moveCursorUp();

	if (kDown & KEY_DOWN && yTilesAway > -1)
		moveCursorDown();

	if (kDown & KEY_RIGHT && xTilesAway < 1) 
		moveCursorRight();

	if (kDown & KEY_LEFT && xTilesAway > -1) 
		moveCursorLeft();		

	if(isPlaceFree())
		gfx->setPieceBackground(BACKGROUND_AVAILABLE);
	else
		gfx->setPieceBackground(BACKGROUND_OCCUPIED);
	
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


void Game::drawPlacedPieces() {
	gfx->drawPlacedPieces();
}

void Game::drawPieceOnPlay() {
	gfx->drawPieceOnPlay();
}


void Game::showScore() {
	gfx->drawScore();
}

void Game::resetMovingPiecePos() {
	xTilesAway = 0;
	yTilesAway = 0;
	placingPosition = 4;


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
	gfx->changePieceOnPlay();
	timerIsSet = false;

	isPlayer1Turn = !(isPlayer1Turn);
	playerHasNotChosen = 1;
	turnsPlayed++;
}

int Game::isTie() {
	if (placedPiecesCnt == 9)
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
	gfx->drawMenu();
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
		gfx->drawMenu();

		

	}
	else if (gameMode == LOCAL_GAME) {
		showScore();
		
		if(!timerIsSet){
			startTimer();
		}

		if(secondsToPlay() == 4){
			timerIsSet = false;
			nextTurn();
			startTimer();

		}
		gfx->drawTime(secondsToPlay());

		gfx->renderTopScreen();
		startLocalGame(kDown);

	}

}

void Game::startLocalGame(u32 kDown) {

	gfx->drawGrid();
	drawPlacedPieces();

	if (playerScoresPoint() == false && isTie() == false) {
		drawPieceOnPlay();
		playerMove(kDown);

	}
	else {
		if (isTie()) {
			printf("\x1b[12;7HLa vieja won!");
		}
		else {
			printf("\x1b[12;7HPlayer %d Won!", playerScoresPoint());
		}


		
		if(countDownNewRound-- < 0){

			if (playerScoresPoint() == PLAYER1)
				addPointsTo(PLAYER1);

			else if(playerScoresPoint() == PLAYER2)
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


void Game::startTimer(){
	difference = svcGetSystemTick() / SYSCLOCK_ARM11;
	timerIsSet = true;
	

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

/**
 * @brief Check if a player has a three on line by adding the values in cell positions.
 * 
 * @return The player scoring. 1 if Player 1, -1 if Player 2, 0 if none.
 */
int Game::playerScoresPoint() {


	//	Horizontal Check
	if (std::abs(placedPos[0] + placedPos[1] + placedPos[2]) == SAME_PIECE)
		return placedPos[0];
	
	if (std::abs(placedPos[3] + placedPos[4] + placedPos[5]) == SAME_PIECE)
		return placedPos[3];

	if (std::abs(placedPos[6] + placedPos[7] + placedPos[8]) == SAME_PIECE)
		return placedPos[6];

	//	Vertical Check
	
	if (std::abs(placedPos[0] + placedPos[3] + placedPos[6]) == SAME_PIECE)
		return placedPos[0];

	if (std::abs(placedPos[1] + placedPos[4] + placedPos[7]) == SAME_PIECE)
		return placedPos[1];

	if (std::abs(placedPos[2] + placedPos[5] + placedPos[8]) == SAME_PIECE)
		return placedPos[2];

	//	Diagonal Check

	if (std::abs(placedPos[0] + placedPos[4] + placedPos[8]) == SAME_PIECE)
		return placedPos[0];

	if (std::abs(placedPos[2] + placedPos[4] + placedPos[6]) == SAME_PIECE)
		return placedPos[2];


	
	return 0;

}







void Game::userInput(){
	// Respond to user input
	hidScanInput();

	kDown = hidKeysDown();
	if (kDown & KEY_START) {
		
		textScene::exitTextScene();
		cfguExit();


		// De-init libs and sprites
		gameScene::stopScene(&gfx->spriteSheet);
		exit(0);	// break in order to return to hbmenu
	}

}

void Game::addPointsTo(int Player){
	if(Player == PLAYER1){
		scoreP1++;
		gfx->setScoreP1(scoreP1);
	}
	else if(Player == PLAYER2){
		scoreP2++;	
		gfx->setScoreP2(scoreP2);
	}
	
}

int Game::secondsToPlay(){
	return  	(svcGetSystemTick() / SYSCLOCK_ARM11) - difference;


}

void Game::setScreens(C3D_RenderTarget* top, C3D_RenderTarget* bot) {
	gfx->setScreens(top, bot);
}



void Game::playAgain() {
	
}

void Game::initScore(){
	gfx->initScore();
	scoreP1 = 0;
	scoreP2 = 0;
}

void Game::deInit(){
	// Deinitialize the scene
	textScene::exitTextScene();
	cfguExit();
	
	// De-init libs and sprites
	gameScene::stopScene(&gfx->spriteSheet);
}


Game::Game(GameGraphics* gfx_) {

	this->gfx= gfx_;
	
	initScore();
	playerHasNotChosen = 1;
	turnsPlayed = 0;
	isPlayer1First = 1;
	isPlayer1Turn = 1;
	placedPiecesCnt = 0;
	placingPosition = 4;

	resetMovingPiecePos();

}

