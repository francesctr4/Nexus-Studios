#pragma once

#include "Timer.h"
#include "Physics.h"
#include "Item.h"
#include <vector>

struct SDL_Texture;

class Puzzle3 {
public:

	Puzzle3();

	virtual ~Puzzle3();

	void Load();

	void Update();

public:

	SDL_Texture* relojArena;
	SDL_Texture* coin;

	bool timerStarted = false;
	Timer coinTimer;

	PhysBody* sensor;
	bool clockPicked = false;
	bool coinPicked = false;

	b2Vec2 posRelojArena = {400,450};

	std::vector<PhysBody*> sensors;

	bool createSensorClock = true;

	bool completed = false;

	int coinCount = 0;

};