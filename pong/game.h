#pragma once

#include "Ball.h"
#include "player.h"

class Game
{
	typedef enum { STATUS_START, STATUS_PLAYING } status_t;
	Player * player=nullptr;
	Player* player2 = nullptr;
	bool player_initialized = false;
	bool debug_mode = false;
	Ball* pongBall = nullptr;
	void spawnpongBall();
	void checkpongBall();
	bool checkHit();
	status_t status = STATUS_START;
	int player1score = 0;
	int player2score = 0;
	bool player1won;
	bool result = false;

	unsigned int window_width = WINDOW_WIDTH;
	unsigned int window_height = WINDOW_HEIGHT;

	void updateStartScreen();
	void updateLevelScreen();
	void drawStartScreen();
	void drawLevelScreen();

	
public:
	void setDebugMode(bool d) { debug_mode = d; }
	bool getDebugMode() const { return debug_mode; }
	void update();
	void draw();
	void init();
	unsigned int getWindowWidth() { return window_width; }
	unsigned int getWindowHeight() { return window_height; }
	float window2canvasX(float x);
	float window2canvasY(float y);
	void setWindowDimensions(unsigned int w, unsigned int h) { window_width = w; window_height = h; }
	Game();
	~Game();
};