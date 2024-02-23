#include "game.h"
#include "graphics.h"
#include "config.h"
#include "gameobject.h"
#include "ball.h"
#include "scancodes.h"


void Game::spawnpongBall()
{
	if (!pongBall)
	{
		pongBall = new Ball(*this);
	}	
}

void Game::checkpongBall()
{
	if (pongBall && !pongBall->isActive())
	{
		delete pongBall;
		pongBall = nullptr;
	}
}

bool Game::checkHit()
{
	if (!player ||!player2 || !pongBall)
	{
		return false;
	}
	Disk dplayer1 = player->getHit();
	Disk dplayer2 = player2->getHit();
	Disk disk2 = pongBall->getHit();

	float dx = dplayer1.cx - disk2.cx;
	float dy = dplayer1.cy - disk2.cy;
	float dx2 = dplayer2.cx - disk2.cx;
	float dy2 = dplayer2.cy - disk2.cy;

	if (sqrt(dx * dx + dy * dy) < (dplayer1.radius + disk2.radius) || (sqrt(dx2 * dx2 + dy2 * dy2) < (dplayer2.radius + disk2.radius)))
	{
		graphics::playSound(std::string(ASSET_PATH) + "ball3_01.mp3", 0.5f);
		return true;
	}
	else {
		return false;
	}
	
}
void Game::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN))
	{
		status = STATUS_PLAYING;
	}
}
void Game::updateLevelScreen()
{

	if (!player_initialized && graphics::getGlobalTime() > 100)
	{
		player = new Player(CANVAS_WIDTH, false, *this);
		player2 = new Player(0, true, *this);
		player_initialized = true;
	}

	if (player)
		player->update();
	if (player2)
		player2->update();

	checkpongBall();
	spawnpongBall();

	if (pongBall)
		pongBall->update();
	if (checkHit())
	{
		pongBall->changeDirection();
	}

	if (pongBall->getX() > CANVAS_WIDTH)
	{
		player2score += 1;
	}
	else
	{
		if (pongBall->getX() < 0)
			player1score += 1;
	}
	if (player1score == 10 || player2score == 10)
	{
		result = true;
		if (player1score > player2score)
		{
			player1won = true;
		}
		else
		{
			player1won = false;
		}
		status = STATUS_START;
		player1score = 0;
		player2score = 0;
	}
}

void Game::drawStartScreen()
{
	graphics::Brush br;
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime() / 400);
	br.texture = std::string(ASSET_PATH) + "glow.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);
	char info[40];
	sprintf_s(info, "Press ENTER to START");
	br.fill_opacity = 0.7f * glow+0.1;
	br.fill_secondary_opacity = 0.3f*glow;
	graphics::drawText(CANVAS_WIDTH/2-150, CANVAS_HEIGHT/2,30,info,br);


	if (result)
	{
		if (player1won)
		{
			char info4[40];
			sprintf_s(info4, "Player 1 won!");
			graphics::drawText(CANVAS_WIDTH / 2 - 110, 70, 40, info4, br);
		}
		else
		{
			char info5[40];
			sprintf_s(info5, "Player 2 won!");
			graphics::drawText(CANVAS_WIDTH / 2 - 110, 70, 40, info5, br);;

		}
		graphics::Brush br;
		br.texture = std::string(ASSET_PATH) + "ezo.png";
		br.outline_opacity = 0.0f;
		graphics::drawRect(CANVAS_WIDTH / 2 - 170, 50, 100 ,80, br);
		br.texture = std::string(ASSET_PATH) + "ezo2.png";
		br.outline_opacity = 0.0f;
		graphics::drawRect(CANVAS_WIDTH / 2 +200, 50, 100, 80, br);
		graphics::resetPose();
	}
}
void Game::drawLevelScreen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "backround.png";
	br.outline_opacity = 0.0f;

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);
	if (player1score < 10 && player2score < 10)
	{
		char info3[6];
		sprintf_s(info3, "Score");
		graphics::drawText(CANVAS_WIDTH / 2 - 65, 50, 50, info3, br);

		char info1[6];
		sprintf_s(info1, "%d", player1score);
		graphics::drawText(CANVAS_WIDTH / 2 + 40, 100, 50, info1, br);

		char info2[6];
		sprintf_s(info2, "% d", player2score);
		graphics::drawText(CANVAS_WIDTH / 2 - 70, 100, 50, info2, br);
	}


	//draw player
	if (player)
		player->draw();
	if (player2)
		player2->draw();
	if (pongBall)
		pongBall->draw();

}


void Game::update()
{
	if (status == STATUS_START)
	{
		updateStartScreen();
	}
	else
	{
		updateLevelScreen();
	}
}

void Game::draw()
{
	if (status == STATUS_START)
	{	
		drawStartScreen();
	}
	else
	{
		drawLevelScreen();
	}
	
}


void Game::init()
{
	graphics::playMusic(std::string(ASSET_PATH) + "8bit.mp3", 0.3f, true, 4000);
	status = STATUS_START;
}

float Game::window2canvasX(float x)
{
	return x * CANVAS_WIDTH / (float)window_width;
}

float Game::window2canvasY(float y)
{
	return y * CANVAS_HEIGHT / (float)window_height;
}

Game::Game()
{

}

Game::~Game()
{
	if (player)
	{
		delete player;
	}
	if (player2)
	{
		delete player2;
	}
}