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

	b2Vec2 Box_Position = { 200,500 };

	PhysBody* TopSensor;
	PhysBody* BottomSensor;

	PhysBody* Box_Collider;
	

};