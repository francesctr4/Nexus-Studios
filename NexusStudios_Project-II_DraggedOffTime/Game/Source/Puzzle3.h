#pragma once

#include "Timer.h"
#include "Physics.h"
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
	PhysBody* sensor;
	bool clockPicked = false;

	b2Vec2 posRelojArena = {400,450};

};