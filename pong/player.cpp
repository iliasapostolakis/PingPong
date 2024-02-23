#include "player.h"
#include "graphics.h"
#include "util.h"
#include "game.h"



Player::Player(float x,bool first,const Game& mygame)
	: GameObject(mygame)
{	
	this->first = first;
	this->pos_x = x;
}


void Player::update()
{
	if (first) {
		if (graphics::getKeyState(graphics::SCANCODE_W))
		{
			pos_y -= speed * graphics::getDeltaTime() / 10.f;
		}
		if (graphics::getKeyState(graphics::SCANCODE_S))
		{
			pos_y += speed * graphics::getDeltaTime() / 10.f;
		}
	}
	else {
		if (graphics::getKeyState(graphics::SCANCODE_UP))
		{
			pos_y -= speed * graphics::getDeltaTime() / 10.f;
		}
		if (graphics::getKeyState(graphics::SCANCODE_DOWN))
		{
			pos_y += speed * graphics::getDeltaTime() / 10.f;
		}
	}
	if (pos_y < 0) pos_y = 0;
	if (pos_y > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT;


}

void Player::draw()
{
	float glow = 0.5f + 0.5f * sinf(graphics::getGlobalTime()/10);
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "red3.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y, 60, 60, br);
	graphics::resetPose();



	if (game.getDebugMode())
		br.outline_opacity = 0.0f;
		br.texture = "";
		br.fill_color[0] = 0.3f;
		br.fill_color[1] = 0.1f;
		br.fill_color[2] = 0.3f;
		br.fill_opacity = 0.3f;
		br.gradient = false;

		Disk player = getHit();
		graphics::drawDisk(player.cx, player.cy, player.radius, br);


}

void Player::init() {

}

Disk Player::getHit() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 30.0f;
	return disk;
}

