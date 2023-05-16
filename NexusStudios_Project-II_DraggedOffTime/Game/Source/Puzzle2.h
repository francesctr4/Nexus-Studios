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

	b2Vec2 Box_Position = { 100,500 };

	PhysBody* TopSensor;
	bool top_collision;

	PhysBody* BottomSensor;
	bool bottom_collision;

	PhysBody* Box_Collider;
	

};