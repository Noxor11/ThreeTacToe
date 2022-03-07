#include "gameGraphics.h"

#define LOCAL_GAME	1
#define ONLINE_GAME 2

static Object* sprites = new Object[MAX_SPRITES];





float textSize = 1.5f;



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

void GameGraphics::drawMenu(){
	textScene::drawMenu(textSize);
}

void GameGraphics::drawScore(){
	textScene::drawScore(textSize, *scoreP1Arr, *scoreP2Arr);

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
	bg->moveYBy(64);
}
void GameGraphics::moveCursorDown() {
	pieceOnPlay->moveYBy(-66);
	bg->moveYBy(-64);

}
void GameGraphics::moveCursorLeft() {
	pieceOnPlay->moveXBy(-66);
	bg->moveXBy(-64);
}
void GameGraphics::moveCursorRight() {
	pieceOnPlay->moveXBy(66);
	bg->moveXBy(64);
}


void GameGraphics::placePiece() {
	gamePieces[gPiecesIndex + 1]->setPos(WIDTH_CENTER, HEIGHT_CENTER);

	Object* tmp = new Object(*gamePieces[gPiecesIndex + 1]);
	tmp->setPos(pieceOnPlay);

	placedPieces[placedPiecesCnt] = tmp;
	placedPiecesCnt++;

	pieceOnPlay->setPos(WIDTH_CENTER, HEIGHT_CENTER);
	
	bg->setPos(WIDTH_CENTER - 0.5f, HEIGHT_CENTER-1);


}

void GameGraphics::changePieceOnPlay(){
	if (gPiecesIndex == 0) {
		gPiecesIndex = 2;
	}
	else {
		gPiecesIndex = 0;
	}

	pieceOnPlay->setPos(WIDTH_CENTER, HEIGHT_CENTER);
	
	bg->setPos(WIDTH_CENTER - 0.5f, HEIGHT_CENTER-1);


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


void GameGraphics::setPieceBackground(int background){
	if(background == BACKGROUND_AVAILABLE)
		bg->setImage(bgAvailable);
	else
		bg->setImage(bgNotAvailable);
}




GameGraphics::GameGraphics() {
	
	// Load graphics
	spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!spriteSheet) svcBreak(USERBREAK_PANIC);
	
	// Create Sprites from sprite sheet


	


	
	gamePieces[0] = new Object(sprites, &spriteSheet, 1);
	gamePieces[1] = new Object(sprites, &spriteSheet, 2);
	gamePieces[2] = new Object(sprites, &spriteSheet, 3);
	gamePieces[3] = new Object(sprites, &spriteSheet, 4);


	scoreP1Arr = new std::string("0");
	scoreP2Arr = new std::string("0");

	gPiecesIndex = 0;
	placedPiecesCnt = 0;
	pieceOnPlay = gamePieces[0];
	grid = new Object(sprites, &spriteSheet, 0);

	arrow = new Object(sprites, &spriteSheet, 6, -150, 0);
	arrow->setPos(70, HEIGHT_CENTER - 15);

	bgAvailable = (new Object(sprites, &spriteSheet, 7))->getImage();
	bgNotAvailable = (new Object(sprites, &spriteSheet, 8))->getImage();
	bg = new Object(bgAvailable);
	bg->setPos(WIDTH_CENTER - 0.5f, HEIGHT_CENTER-1);





}