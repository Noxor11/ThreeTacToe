#pragma once
#include "gameObjects.h"
#include "textScene.h"
#include <string>

#define COUNTDOWN	100
#define UNSET		-1
#define LOCAL_GAME	1
#define ONLINE_GAME 2
#define TIE			3



class Game {

	int gPiecesIndex;
	int placedPiecesCnt;
	int placedPos[9] = {};
	int placingPosition;
	int turnsPlayed = 0;
	int gameMode = UNSET;
	bool isPlayer1Turn;

	int scoreP1 = 0;
	std::string* scoreP1Arr = new std::string("0");

	int scoreP2 = 0;
	std::string* scoreP2Arr = new std::string("0");


	bool playerHasNotChosen = 1;

	int xTilesAway = 0;
	int yTilesAway = 0;

	int countDownNewRound = COUNTDOWN;

	Object* grid;
	Object* gamePieces[4] = {};
	Object* placedPieces[9] = {};
	Object* arrow;


	Object* pieceOnPlay;


	C3D_RenderTarget* topScreen;
	C3D_RenderTarget* bottomScreen;


	u32 kDown;

	bool isTie();
	bool isPlaceFree();
	void nextTurn();
	void nextRound();
	bool placePiece();
	void drawPlacedPieces();
	void drawPieceOnPlay();
	void showScore();
	void drawGameMenu();


public:

	void userInput(C2D_SpriteSheet* spriteSheet);

	void playerMove(u32 kDown);

	void chooseMode();
	void startLocalGame(u32 kDown);
	int gameOver();
	void playAgain();
	void addPointsTo(int& playerScore, std::string* scoreArr);

	void setScreens(C3D_RenderTarget* tScreen, C3D_RenderTarget* botScreen);


	Game(Object* grid, Object* p1Piece, Object* p1SelectedPiece, Object* p2Piece, Object* p2SelectedPiece, Object* arrow);
};


struct Player {
	Object* piece;
	Player(Object* pi);
	Player();
};