#pragma once

#include "gameobject.h"
#include "config.h"


class Player : public GameObject, public Hit
{
	float speed = 10.0f;
	float pos_x = 0, pos_y = CANVAS_HEIGHT / 2;
	float height = 50;
	bool first;
	
public:
	Player(float x,bool first,const class Game & mygame);
	void update() override;
	void draw() override;
	void init() override;
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	Disk getHit() const override;

	
};