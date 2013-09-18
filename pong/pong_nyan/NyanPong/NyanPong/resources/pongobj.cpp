#include "pongh.h"
#include "AIE.h"
#include "KeyCodes.h"
#include <string>
#include <cmath>
#include <assert.h>
#include <crtdbg.h>
#include <ctime>
#include <iostream>

// get the magnitude of a vector
float getMagnitude(vector2 &v){
	return sqrt(v.x*v.x + v.y*v.y);
}

// sort an array of integers in descending order
void sort(int array[], int size) {
	for(int i=0; i<size; i++) {
		for(int j=0; j<size; j++) {
			if(array[i] > array[j]) {
				int tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;				
			}
		}	
	}
}

// will test if an object has gone outside the screen boundaries
// if the object has gone off the screen, this function will also modify
// the objects speed so that it will move back onto the screen
// returns true if the object's x or y coordinate is off the screen
bool testOnScreen(movableObject& obj){
	if(obj.position.x > SCREEN_X) {
		obj.speed.x *= -1;
		return true;
	}
	if(obj.position.x < 0) {
		obj.speed.x *= -1;
		return true;
	}
	if(obj.position.y > SCREEN_Y) {
		obj.speed.y *= -1;
	}
	if(obj.position.y < 0) {
		obj.speed.y *= -1;
	}
	return false;
}

// updates the position of the ball
// adds the balls current velocity to its current position to get the 
// new position
void updateBallPosition(movableObject &obj) {
	obj.position = vectorAdd(obj.position, obj.speed);
}

// check if the ball has collided with the paddle
// returns true if a collision occurred
bool checkPaddleCollision(movableObject& ball, movableObject& player) {
	int speed = ball.speed.x;
	
	int ballHalfW = ball.width>>1;
	int playerHalfW = player.width>>1;
	int playerHalfH = player.height>>1;
	
	if(speed == 0)
		return false;

	if(speed < 0){
		if(ball.position.x - ballHalfW < player.position.x + playerHalfW && 
			ball.position.y > player.position.y - playerHalfH &&
			ball.position.y < player.position.y + player.height){
				return true;
		}
	}
	else {
		if(ball.position.x + ballHalfW > player.position.x - playerHalfW && 
			ball.position.y > player.position.y - playerHalfH &&
			ball.position.y < player.position.y + player.height){
				return true;
		}
	}
	return false;
}

// check if one object has collided with another object
// returns true if the two objects have collided
bool checkCollision(movableObject& obj1, movableObject& obj2) {	
	vector2 diff = vectorSubtract(obj1.position, obj2.position);
	float mag = getMagnitude(diff);
	
	if(mag > 0 && mag < obj1.height){
		// collision
		obj1.speed = multiplyScalar( getNormal(diff), 5);
		obj2.speed = multiplyScalar( getNormal(diff), -5);
		return true;
	}
	return false;
}

// the player's paddle position will be updated according the position of the ball.
// this is how we get the computer players updating their paddles
void seek(movableObject &player, movableObject& ball){
	float speed = sqrt(ball.speed.x*ball.speed.x + ball.speed.y*ball.speed.y);

	
	if (player.position.y < ball.position.y) 
			player.position.y = ball.position.y;
	else if (player.position.y > ball.position.y)
		player.position.y = ball.position.y;
	else if (player.position.x < ball.position.x)
		player.position.y = player.position.y;
	/*
	if(player.position.y < ball.position.y - speed) {
		int diff = ball.position.y - player.position.y;
		if(diff > speed)
			player.position.y += speed;
		else
			player.position.y += diff;
	}
	else if (player.position.y > ball.position.y + speed) {
		int diff = player.position.y - ball.position.y;
		if(diff > speed)
			player.position.y -= speed;
		else
			player.position.y -= diff;
	}
	*/
}

void movePlayer(movableObject &player)
{
	
	float speed = sqrt(ball.speed.x*ball.speed.x + ball.speed.y*ball.speed.y - 30);

	if(IsKeyDown('S') && (checkCollision(player1, bottom) == false) || IsKeyDown(GLFW_KEY_DOWN) && (checkCollision(player1, bottom) == false)) {
		int diff = player.position.y;
		player.position.y += speed;
		//if (checkCollision(player1, bottom) == true)
			//player.position.y -= 10;
	}
	else if (IsKeyDown('W') && (checkCollision(player1, top) == false) || IsKeyDown(GLFW_KEY_UP) && (checkCollision(player1, top) == false)) {
		int diff = player.position.y;
		player.position.y -= speed;
		//if (checkCollision(player1, top) == true)
			//player.position.y += 10;
	}

}

// initialize all the variables in the game
void initGame() {
	srand(time(0));

	// Now load some sprites
	//bgMenu = CreateSprite( "./images/menu.jpg", SCREEN_X, SCREEN_Y, true);
	//MoveSprite(bgMenu, SCREEN_X>>1, SCREEN_Y>>1);
	bgImage = CreateSprite( "./images/bg.jpg", SCREEN_X, SCREEN_Y, true );
	MoveSprite(bgImage, SCREEN_X>>1, SCREEN_Y>>1);

	player1.sprite = CreateSprite( "./images/cat1.png", PLAYER1_W, PLAYER1_H, true );
	player2.sprite = CreateSprite( "./images/cat2.png", PLAYER2_W, PLAYER2_H, true );
	ball.sprite = CreateSprite( "./images/icecream.png", BALL_W, BALL_H, true );
	
}

// destroy all the sprites and clean up any memory
void destroyGame() {
	//DestroySprite(bgMenu);
	DestroySprite(bgImage);
	DestroySprite(player1.sprite);
	DestroySprite(player2.sprite);
	DestroySprite(ball.sprite);
}

// update the game logic here
void updateGame() {
	updateBallPosition(ball);
	movePlayer(player1);
	if(ball.speed.x < 0)
		seek(player2, ball);
	
	if( testOnScreen(ball) ) {
		// ball hit side of screen
		if(ball.position.x < 50) {
			// player 1 lost
			player2Score++;
		}
		else {
			// player 2 lost
			player1Score++;
		}
	}

	if(g_gameOver == false) {
		if( abs(player1Score - player2Score) >= 3) {
			// Game Over
			g_gameOver = true;

			int highestScore = player1Score;
			if(player2Score > highestScore) {
				highestScore = player2Score;
			}

			for(int i=0; i<5; i++) {
				if(highestScore > g_highScores[i]) {
					g_highScores[i] = highestScore;
					break;
				}
			}

			// sort the high scores array
			sort(g_highScores, 5);
		}
	}

	if(ball.speed.x < 0) {
		if(checkPaddleCollision(ball, player1) == true)  {
			ball.speed.x *= -1;
		}
	}
	else {
		if(checkPaddleCollision(ball, player2) == true)  {
			ball.speed.x *= -1;
		}
	}


	RotateSprite(player1.sprite, 0);
	MoveSprite(player1.sprite, player1.position.x, player1.position.y);

	RotateSprite(player2.sprite, 0 );
	MoveSprite(player2.sprite, player2.position.x, player2.position.y);

	MoveSprite(ball.sprite, (int)ball.position.x, (int)ball.position.y);
}

// draws each frame of the game
void drawGame() {
	static char outScore1[15] = {'\n'};
	static char outScore2[15] = {'\n'};

	DrawSprite(ball.sprite);
	DrawSprite(player1.sprite);
	DrawSprite(player2.sprite);

	sprintf(outScore1, "Player 1: %d", player1Score);
	sprintf(outScore2, "Player 2: %d", player2Score);
	// draw the scores
	DrawString(outScore1, 50, 50, SColour(255,0,0,255));
	DrawString(outScore2, 1000, 50, SColour(0,255,0,255));

	if(g_gameOver == true) {
		DrawString("Game Over", SCREEN_X / 2, 300);

		char score[15];
		int y = 350;
		for(int i=0; i<5; i++) {
			if(g_highScores[i] != 0) {
				sprintf(score, "player %d: %d", i, g_highScores[i]);
				DrawString(score, SCREEN_X / 2, y);
				y += 30;
			}
		}
	}

	DrawSprite(bgImage);
}