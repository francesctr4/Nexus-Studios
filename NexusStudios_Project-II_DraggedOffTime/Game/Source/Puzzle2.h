#pragma once

#include "Timer.h"
#include "Physics.h"
#include <vector>

struct SDL_Texture;

class Puzzle2 {
public:

	Puzzle2();

	virtual ~Puzzle2();

	void Load();

	void Update();

public:

	SDL_Texture* texture;

	//Box 1
	float NewPosX1;
	b2Vec2 Box1_Position = { 208,576 };
	PhysBody* TopSensor1;
	bool top_collision1;

	PhysBody* BottomSensor1;
	bool bottom_collision1;

	PhysBody* Box1_Collider;

	//Box 2
	float NewPosX2;
	b2Vec2 Box2_Position = { 400,288 };
	PhysBody* TopSensor2;
	bool top_collision2;

	PhysBody* BottomSensor2;
	bool bottom_collision2;

	PhysBody* Box2_Collider;

	//Box 3
	float NewPosX3;
	b2Vec2 Box3_Position = { 592,592 };
	PhysBody* TopSensor3;
	bool top_collision3;

	PhysBody* BottomSensor3;
	bool bottom_collision3;

	PhysBody* Box3_Collider;

	//Box 4
	float NewPosX4;
	b2Vec2 Box4_Position = { 672,336 };
	PhysBody* TopSensor4;
	bool top_collision4;

	PhysBody* BottomSensor4;
	bool bottom_collision4;

	PhysBody* Box4_Collider;

	//Box 5
	float NewPosX5;
	b2Vec2 Box5_Position = { 752,192 };
	PhysBody* TopSensor5;
	bool top_collision5;

	PhysBody* BottomSensor5;
	bool bottom_collision5;

	PhysBody* Box5_Collider;

};