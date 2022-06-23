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

	if(gameMode == CLASSIC_MODE){

		if (kDown & KEY_UP && yTilesAway < 1) 
			moveCursorUp();

		if (kDown & KEY_DOWN && yTilesAway > -1)
			moveCursorDown();

		if (kDown & KEY_RIGHT && xTilesAway < 1) 
			moveCursorRight();

		if (kDown & KEY_LEFT && xTilesAway > -1) 
			moveCursorLeft();	

		else if (kDown & KEY_A) {	//	Place if there's not another piece below
			if (placePiece()) {

				//	Piece to place belongs to...
				if (isPlayer1Turn)
					placedPos[placingPosition] = PLAYER1;
				else
					placedPos[placingPosition] = PLAYER2;
					
				playerHasNotChosen = 0;
			}

		}	
			
		if(isPlaceFree())
			gfx->setPieceBackground(placingPosition, BACKGROUND_AVAILABLE);
		else
			gfx->setPieceBackground(placingPosition, BACKGROUND_OCCUPIED);
		
	} else{

		int touchi = getTouchPlacingPosition();
		if(touchi != UNSET){

			moverCursorToPlace(touchi);

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



	
}

int Game::getTouchPlacingPosition(){
	formerTouch = touch;
	hidTouchRead(&touch);

	int beginX = (gfx->getGrid()->px() - gfx->getGrid()->getSprite()->params.pos.w / 2) + 5;
	int endX   = (gfx->getGrid()->px() + gfx->getGrid()->getSprite()->params.pos.w / 2) + 5;

	int beginY = (gfx->getGrid()->py() - gfx->getGrid()->getSprite()->params.pos.h / 2) + 5;
	int endY   = (gfx->getGrid()->py() + gfx->getGrid()->getSprite()->params.pos.h / 2) + 8;
	
	if(formerTouch.px == 0 && formerTouch.py == 0){

		//	If within range of grid...
		if(touch.px > beginX  && touch.px < endX && touch.py > beginY  && touch.py < endY){

			//	Get position from x and y coords
			int x_index = (touch.px / ((endX - beginX - 8) / 3)) - 1;
			if(x_index > 2)
				x_index = 2;
			if(x_index < 0)
				x_index = 0;

			int y_index = (touch.py / ((endY - beginY ) / 2.7));
			if(y_index > 2)
				y_index = 2;
			if(y_index < 0){
				y_index = 0;
			}

			xTilesAway = x_index - 1;
			yTilesAway = -(y_index - 1);

			int index = x_index + (y_index * 3);
			return index;
		}
	}

	return UNSET;


}

void Game::moverCursorToPlace(int index){
	gfx->moveCursorToPlace(index);

	placingPosition = index;
	
	

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
		gfx->placePiece(placingPosition);
				
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
	if(gameMode == CLASSIC_MODE)
		gfx->setPieceBackground(placingPosition, BACKGROUND_AVAILABLE);
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
	gfx->drawOnlineLocalMenu();
}

void Game::chooseMode() {
	gfx->renderTopScreen();
	
	
	if (gameModeOnlineLocal < 1) {
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
		gfx->drawOnlineLocalMenu();

		

	}
	else if (gameModeOnlineLocal == LOCAL_GAME) {

		if(gameMode < 0){

			if (kDown & KEY_UP) {
				gfx->selectMode(CLASSIC_MODE);
				gameMode = -CLASSIC_MODE;
			}

			if (kDown & KEY_DOWN) {
				gfx->selectMode(RUSH_MODE);
				gameMode = -RUSH_MODE;
			}

			if (kDown & KEY_A) {
				gameMode = -gameMode;
			}

			//	Go back
			if (kDown & KEY_B) {
				gameModeOnlineLocal = UNSET;
			}

			gfx->drawArrow();
			gfx->drawClassicRushMenu();

		} else if(gameMode == RUSH_MODE){

			showScore();
			gfx->showPieceOnPlayTopScreen();
			
			if(!timerIsSet){
				startTimer();
			}

			if(secondsToPlay() == 4){
				timerIsSet = false;
				nextTurn();
				startTimer();

			}
			gfx->drawTime(secondsToPlay());

			gfx->renderBotScreen();
			startLocalGame(kDown);
		} else{

			gfx->showPieceOnPlayTopScreen();
			showScore();

			gfx->renderBotScreen();
			startLocalGame(kDown);
		}

	}
	else if (gameModeOnlineLocal == ONLINE_GAME) {
		showScore();
		
		if(!timerIsSet){
			startTimer();
		}

		//	Go back
		if (kDown & KEY_B) {
			gameModeOnlineLocal = UNSET;
		}

		gfx->renderBotScreen();

	}

}



void Game::startLocalGame(u32 kDown) {

	gfx->drawGrid();
	drawPlacedPieces();

	if (playerScoresPoint() == false && isTie() == false) {
		if(gameMode == CLASSIC_MODE)
			drawPieceOnPlay();
		playerMove(kDown);

	}
	else {
		
		timerIsSet = false;

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
	gameModeOnlineLocal = -mode;

}

void Game::confirmSelect() {
	gameModeOnlineLocal *= -1;	//	select game by making it positive
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
	isPlayer1First = 1;
	isPlayer1Turn = 1;
	placedPiecesCnt = 0;
	placingPosition = 4;

	resetMovingPiecePos();

	formerTouch.px = 0;
	formerTouch.py = 0;

}

