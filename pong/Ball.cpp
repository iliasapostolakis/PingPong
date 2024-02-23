#include "Ball.h"
#include "graphics.h"
#include "config.h"
#include <random>
#include "util.h"
#include "game.h"
#include <time.h>




void Ball::update()
{
	pos_x += direction2 * speedX * graphics::getDeltaTime();
	pos_y += direction3 * speedY * graphics::getDeltaTime();
	rotation += 1.5f * graphics::getDeltaTime();
	rotation = fmodf(rotation, 360);
	if (pos_y >= CANVAS_HEIGHT) {
		direction3 = -1;
	}
	else if (pos_y <= 0) {
		direction3 = 1;
	}

	if (pos_x < 0 || pos_x>CANVAS_WIDTH )
	{
		active = false;
	}
}



void Ball::draw()
{
	graphics::setOrientation(rotation);
	brush.texture = std::string(ASSET_PATH) + "pong.png";
	brush.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, BALL_HEIGHT, BALL_WIDTH, brush);
	graphics::resetPose();

	if (game.getDebugMode())
	{
		graphics::Brush br;
		br.outline_opacity = 0.0f;
		br.texture = "";
		br.fill_color[0] = 1.0f;
		br.fill_color[1] = 1.0f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.0f;
		br.gradient = false;
		Disk ballhit = getHit();
		graphics::drawDisk(ballhit.cx, ballhit.cy, ballhit.radius, br);

	}
}
float Ball :: getSpeed() {
	return speed;
}
void Ball::changeDirection() {
	int d;
	if (rand() % 2 == 0) {
		d = 1;
	}
	else {
		d = -1;
	}
	direction2 = (-1)* direction2;
	direction3 = (d) * direction3;
	speedX = (randd()+0.1) ;
	speedY = (randd()+0.1) ;
}
int Ball::getDirection() {
	return direction2;
}

float Ball::getX()
{
	return pos_x;
}

float Ball::getY()
{
	return pos_y;
}


void Ball::init()
{
	speedX = 0.2f;
	speedY = 0.2f;
	pos_x = CANVAS_WIDTH / 2;
	pos_y = CANVAS_HEIGHT / 2;
	size = 50;
	rotation = 360 * randd();
}


Ball::Ball(const class Game& mygame)
	: GameObject(mygame)
{
	init();
}

Ball::~Ball()
{
}

Disk Ball::getHit() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size*0.25f;
	return disk;
}