#pragma once

#include "Timer.h"
#include "Physics.h"
#include <vector>
	
struct SDL_Texture;

class Infierno {
public:

	Infierno();

	virtual ~Infierno();

	void Start();

	void Update();

	void CleanUp();

public:

	bool canLoad = true;
	bool canClean = false;

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

	b2Vec2 posButton1 = { 544,352 };
	b2Vec2 posButton2 = { 720,352 };
	b2Vec2 posButton3 = { 544,528 };
	b2Vec2 posButton4 = { 720,528 };

	bool map_selector = false;
	bool infierno = false;

};