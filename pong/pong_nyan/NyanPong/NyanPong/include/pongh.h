// last edit 9/24/2013 - Will Gilstrap
//////////////////////////////////////////////////////////////////////////
#ifndef _PONGH_H_
#define _PONGH_H_

#include "AIE.h"
#include "KeyCodes.h"
#include <string>
#include <cmath>
#include <assert.h>
#include <crtdbg.h>
#include <ctime>
#include <iostream>
#include "pongh.h"

struct vector2{
	float x;
	float y;
};

struct moveableObject{
	vector2 position;
	vector2 speed;
	int sprite;
	int width;
	int height;
};

const int SPEED = 10;
const int SCREEN_X = 1280;
const int SCREEN_Y = 780;

const int PLAYER1_X = 100;
const int PLAYER1_W = 100;
const int PLAYER1_H = 144;

const int PLAYER2_X = 1200;
const int PLAYER2_W = 83;
const int PLAYER2_H = 128;

const int BALL_W = 64;
const int BALL_H = 92;


// global variables 
unsigned int bgImage = -1;
//unsigned int bgMenu = -1;
moveableObject player1 = {PLAYER1_X, 100, 0, 0, -1 , PLAYER1_W, PLAYER1_H};
moveableObject player2 = {PLAYER2_X, 100, 0, 0, -1, PLAYER2_W, PLAYER2_H};
moveableObject ball = {500, 500, 5+(rand()%40)/10, 5+(rand()%50)/10, -1, BALL_W, BALL_H};
moveableObject top = {0, 0, 0, 0, -1, 1280, 10};	// collision pads for paddle
moveableObject bottom = {0, 780, 0, 0, -1, 1280, 10};	// collision pads paddle
int g_highScores[5] = {0};
bool g_gameOver = false;
bool menuExit = false;

int player1Score = 0;	// player 1 score
int player2Score = 0;	// player 2 score
int frameCounter = 0;

/*
vector2 vectorSubtract(vector2 &v, float s);
vector2 vectorAdd(vector2 &v, float s);
vector2 multiplyScalar(vector2 &v, float s);
vector2 vectorSubtract(vector2 &v, vector2 &v2);
vector2 vectorAdd(vector2 &v, vector2 &v2);
vector2 getNormal(vector2 &v);
float getMagnitude(vector2 &v);
void sort(int array[], int size);
bool testOnScreen(moveableObject& obj);
void updateBallPosition(moveableObject &obj);
bool checkPaddleCollision(moveableObject& ball, moveableObject& player);
bool checkCollision(moveableObject& obj1, moveableObject& obj2);
void seek(moveableObject &player, moveableObject& ball);
void movePlayer(moveableObject &player);
void initGame();
void destroyGame();
void updateGame();
void drawGame();
*/

#endif