#pragma once

#include "Timer.h"
#include "Physics.h"
#include <vector>

struct SDL_Texture;

class Puzzle {
public:

	Puzzle();

	virtual ~Puzzle();

	void Load();

	void Update();

	void Draw();

public:

	SDL_Texture* texture;

	PhysBody* sensor1;
	bool sensor1Pressed = false;

	PhysBody* sensor2;
	bool sensor2Pressed = false;

	PhysBody* sensor3;
	bool sensor3Pressed = false;

	PhysBody* sensor4;
	bool sensor4Pressed = false;

	uint buttonPressed;

	bool everySensorPressed = false;

	Timer failTimer;
	uint fail;
	bool failed = false;
	bool failedFX = false;

	uint correct;
	bool completed = false;

	std::vector<int> order;
	std::string combination;

	b2Vec2 posButton1 = {300,420};
	b2Vec2 posButton2 = {350,420};
	b2Vec2 posButton3 = {300,470};
	b2Vec2 posButton4 = {350,470};

};