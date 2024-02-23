#pragma once
#include "gameobject.h"
#include "graphics.h"
#include <time.h>

class Ball : public GameObject, public Hit
{
	float pos_x, pos_y;
	float speed;
	float size;
	float rotation;
	graphics::Brush brush;
	bool active = true;
	int direction2 = 1;
	int direction3 = 1;
	float speedX;
	float speedY;

public:
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	float getX();
	float getY();
	float getSpeed();
	void changeDirection();
	int getDirection();
	bool CheckchangeDirection();
	Ball(const class Game & mygame);
	~Ball();
	Disk getHit() const override;
};
