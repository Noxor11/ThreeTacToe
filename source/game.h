#pragma once
#include "gameObjects.h"
#include "textScene.h"
#include "gameGraphics.h"
#include <string>
#include <array>


#define COUNTDOWN	100
#define UNSET		-1
#define LOCAL_GAME	1
#define ONLINE_GAME 2
#define TIE			3



class Game {

	std::array<int, 9> placedPos = {};


	long difference = 0;



	int placedPiecesCnt;
	int placingPosition;
	int gameMode = UNSET;
	bool isPlayer1Turn;
	bool isPlayer1First;

	int scoreP1;
	int scoreP2;


	bool playerHasNotChosen;
	int xTilesAway;
	int yTilesAway;



	int countDownNewRound = COUNTDOWN;

	GameGraphics* gfx;
	
	bool timerIsSet = false;


	u32 kDown;

	int isTie();
	bool placePiece();
	bool isPlaceFree();
	void nextTurn();
	void nextRound();
	void resetMovingPiecePos();
	void drawPlacedPieces();
	void drawPieceOnPlay();
	void showScore();
	void drawGameMenu();
	void selectMode(int mode);
	void confirmSelect();
	void moveCursorUp();
	void moveCursorDown();
	void moveCursorLeft();
	void moveCursorRight();
	void checkForMovement();
	void initScore();
	void playerMove(u32 kDown);
	void startLocalGame(u32 kDown);
	void playAgain();
	void addPointsTo(int Player);
	int playerScoresPoint();
	void startTimer();

public:
	void chooseMode();
	void userInput();
	void setScreens(C3D_RenderTarget* top, C3D_RenderTarget* bot);
	int secondsToPlay();
	void deInit();

	Game(GameGraphics* gfx_);
};
