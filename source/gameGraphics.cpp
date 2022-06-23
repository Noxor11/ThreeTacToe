#include "gameGraphics.h"
#include "game.h"




#define CELL_SPACE_DIFFERENCE 	66
#define BG_SPACE_DIFFERENCE		64

#define X_PIECE_BLACK 	0
#define X_PIECE_RED		1

#define O_PIECE_BLACK 	2
#define O_PIECE_BLUE	3


static Object* sprites = new Object[MAX_SPRITES];


 


float textSize = 1.5f;



void GameGraphics::setScreens(C3D_RenderTarget* tScreen, C3D_RenderTarget* botScreen) {
	topScreen = tScreen;
	bottomScreen = botScreen;
}



void GameGraphics::prepareNextRound() {
	for (int i = 0; i < placedPiecesCnt; i++)
		placedPieces[i] = {};

	placedPiecesCnt = 0;
	changeFirstPiece();
	pieceOnPlay = gamePieces[gPiecesIndex];
	
}


void GameGraphics::drawPieceOnPlay() {
	gameScene::draw(bg);
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

void GameGraphics::drawOnlineLocalMenu(){
	textScene::drawOnlineLocalMenu(textSize);
}

void GameGraphics::drawClassicRushMenu(){
	textScene::drawClassicRushMenu(textSize);
}

void GameGraphics::drawScore(){
	textScene::drawScore(textSize, *scoreP1Arr, *scoreP2Arr);

}

void GameGraphics::showPieceOnPlayTopScreen(){
	gameScene::draw(&staticPieceOnPlay);
}

void GameGraphics::renderTopScreen() {
	gameScene::renderScene(topScreen);
}

void GameGraphics::renderBotScreen() {
	gameScene::renderScene(bottomScreen);
}

/**
 * @brief Selects mode not only for online / local game,
 * but also for classic / rush mode
 * 
 * @param mode 
 */
void GameGraphics::selectMode(int mode) {
	switch (mode) {
	case 1:
		arrow->setPos(70, HEIGHT_CENTER - 15);
		break;
	case 2:
		arrow->setPos(70, HEIGHT_CENTER + 15);
		break;
	}

}

void GameGraphics::moveCursorUp() {
	pieceOnPlay->moveYBy(66);
	bg->moveYBy(64);
	printf("Position X: %f Y: %f\n", pieceOnPlay->px(), pieceOnPlay->py());

}
void GameGraphics::moveCursorDown() {
	pieceOnPlay->moveYBy(-66);
	bg->moveYBy(-64);


}
void GameGraphics::moveCursorLeft() {
	pieceOnPlay->moveXBy(-66);
	bg->moveXBy(-64);
	printf("Position X: %f Y: %f\n", pieceOnPlay->px(), pieceOnPlay->py());

}
void GameGraphics::moveCursorRight() {
	pieceOnPlay->moveXBy(66);
	bg->moveXBy(64);
	printf("Position X: %f Y: %f\n", pieceOnPlay->px(), pieceOnPlay->py());

}

void GameGraphics::moveCursorToPlace(int index){
	int piece_X = SCREEN_WIDTH / 2;
	int Piece_Y = SCREEN_HEIGHT / 2;

	int bg_X = WIDTH_CENTER - 0.5f;
	int bg_Y = HEIGHT_CENTER-1;

	switch (index){
	case 0:
		piece_X -= 66;
		Piece_Y -= 66;

		bg_X -= BG_SPACE_DIFFERENCE;
		bg_Y -= BG_SPACE_DIFFERENCE;
		break;
	
	case 1:
		Piece_Y -= 66;
		bg_Y -= BG_SPACE_DIFFERENCE;
		break;

	case 2:
		piece_X += 66;
		Piece_Y -= 66;

		bg_X += BG_SPACE_DIFFERENCE;
		bg_Y -= BG_SPACE_DIFFERENCE;
		break;

	case 3:
		piece_X -= 66;
		bg_X -= BG_SPACE_DIFFERENCE;
		break;

	//	It's already in the middle
	// case 4:
	// 	break;

	case 5:
		piece_X += 66;
		bg_X += BG_SPACE_DIFFERENCE;
		break;

	case 6:
		piece_X -= 66;
		Piece_Y += 66;

		bg_X -= BG_SPACE_DIFFERENCE;
		bg_Y += BG_SPACE_DIFFERENCE;
		break;

	case 7:
		Piece_Y += 66;
		bg_Y += BG_SPACE_DIFFERENCE;
		break;

	case 8:
		piece_X += 66;
		Piece_Y += 66;

		bg_X += BG_SPACE_DIFFERENCE;
		bg_Y += BG_SPACE_DIFFERENCE;
		break;


	}

	pieceOnPlay->setX(piece_X);
	pieceOnPlay->setY(Piece_Y);

	bg->setX(bg_X);
	bg->setY(bg_Y);

}


void GameGraphics::placePiece(int placing_position) {
	gamePieces[gPiecesIndex + 1]->setPos(WIDTH_CENTER, HEIGHT_CENTER);

	Object* tmp = new Object(*gamePieces[gPiecesIndex + 1]);
	tmp->setPos(pieceOnPlay);

	placedPieces[placedPiecesCnt] = tmp;

	placedPiecesCnt++;

	pieceOnPlay->setPos(WIDTH_CENTER, HEIGHT_CENTER);
	
	bg->setPos(WIDTH_CENTER - 0.5f, HEIGHT_CENTER-1);


}



void GameGraphics::changePieceOnPlay(){
	if (gPiecesIndex == X_PIECE_BLACK) {
		gPiecesIndex = O_PIECE_BLACK;
	}
	else {
		gPiecesIndex = X_PIECE_BLACK;
	}

	pieceOnPlay->setPos(WIDTH_CENTER, HEIGHT_CENTER);
	
	bg->setPos(WIDTH_CENTER - 0.5f, HEIGHT_CENTER-1);

	currentPieceImage = gamePieces[gPiecesIndex]->getImage();
	pieceOnPlay = gamePieces[gPiecesIndex];

	staticPieceOnPlay.setImage(gamePieces[gPiecesIndex + 1]->getImage());

}

void GameGraphics::changeFirstPiece() {
	if(wasXFirst){
		gPiecesIndex = O_PIECE_BLACK;
	} else{
		gPiecesIndex = X_PIECE_BLACK;
	}

	wasXFirst = !wasXFirst;

	currentPieceImage = gamePieces[gPiecesIndex]->getImage();
	staticPieceOnPlay.setImage(gamePieces[gPiecesIndex + 1]->getImage());

}

void GameGraphics::setScoreP1(int scoreP1){
	delete scoreP1Arr;
	scoreP1Arr = new std::string(std::to_string(scoreP1));
}

void GameGraphics::setScoreP2(int scoreP2){
	delete scoreP2Arr;
	scoreP2Arr = new std::string(std::to_string(scoreP2));
}

void GameGraphics::initScore(){
	delete scoreP1Arr;
	delete scoreP2Arr;
	scoreP1Arr = new std::string("0");
	scoreP2Arr = new std::string("0");

}

void GameGraphics::drawTime(int seconds){
		textScene::drawTime(seconds, textSize);
}


void GameGraphics::setPieceBackground(int index, int background){
	if(background == BACKGROUND_AVAILABLE){
		bg->setImage(bgAvailable);
		pieceOnPlay->setImage(currentPieceImage);
	}
	else{	
		bg->setImage(bgNotAvailable);
	}
}



Object* GameGraphics::getGrid(){
	return grid;
}





GameGraphics::GameGraphics() {
	
	// Load graphics
	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!spriteSheet) svcBreak(USERBREAK_PANIC);
	
	// Create Sprites from sprite sheet





	


	
	gamePieces[X_PIECE_BLACK] 	= new Object(sprites, &spriteSheet, 1);
	gamePieces[X_PIECE_RED] 	= new Object(sprites, &spriteSheet, 2);
	gamePieces[O_PIECE_BLACK] 	= new Object(sprites, &spriteSheet, 3);
	gamePieces[O_PIECE_BLUE] 	= new Object(sprites, &spriteSheet, 4);



	scoreP1Arr = new std::string("0");
	scoreP2Arr = new std::string("0");

	gPiecesIndex = 0;
	placedPiecesCnt = 0;
	pieceOnPlay = gamePieces[0];

	staticPieceOnPlay = Object(sprites, &spriteSheet, 2);
	staticPieceOnPlay.setPos( (SCREEN_WIDTH + 80) / 2, (SCREEN_HEIGHT / 2) + 20);


	grid = new Object(sprites, &spriteSheet, 0);

	arrow = new Object(sprites, &spriteSheet, 6, -150, 0);
	arrow->setPos(70, HEIGHT_CENTER - 15);

	bgAvailable = (new Object(sprites, &spriteSheet, 7))->getImage();
	bgNotAvailable = (new Object(sprites, &spriteSheet, 8))->getImage();
	bg = new Object(bgAvailable);
	bg->setPos(WIDTH_CENTER - 0.5f, HEIGHT_CENTER-1);


	currentPieceImage = pieceOnPlay->getImage();



}