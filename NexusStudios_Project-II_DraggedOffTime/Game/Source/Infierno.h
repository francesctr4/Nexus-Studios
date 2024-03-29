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

	void TeleportInfierno();

	void TeleportInfiernoReversa();

	void TeleportInfiernoJovani();

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

	bool lobby = false;
	bool prehistoria = false;
	bool medieval = false;
	bool infierno = false;
	Timer selectionTimer;
	bool timerActivated = false;

	PhysBody* TP_Infierno_0;
	PhysBody* TP_Infierno_1;
	PhysBody* TP_Infierno_2;
	PhysBody* TP_Infierno_3;
	PhysBody* TP_Infierno_4;
	PhysBody* TP_Infierno_5;
	PhysBody* TP_Infierno_Cofre;
	PhysBody* TP_Infierno_Jovani;
	PhysBody* Tp_Puzzle1;
	PhysBody* Tp_Puzzle2;
	PhysBody* Tp_Puzzle3;

	bool Tp_1 = true;
	bool Tp_2 = true;
	bool Tp_3 = true;
	bool Tp_4 = true;
	bool Tp_5 = true;
	bool Tp_Jovani = true;
	bool Tp_Puzzle_1 = true;
	bool Tp_Puzzle_2 = true;
	bool Tp_Puzzle_3 = true;
	bool Tp_Boss = false;

	PhysBody* TP_Infierno_0_Reversa;
	PhysBody* TP_Infierno_1_Reversa;
	PhysBody* TP_Infierno_2_Reversa;
	PhysBody* TP_Infierno_3_Reversa;
	PhysBody* TP_Infierno_4_Reversa;
	PhysBody* TP_Infierno_5_Reversa;
	PhysBody* TP_Infierno_Jovani_Reversa;
	PhysBody* Tp_Puzzle1_Reversa;
	PhysBody* Tp_Puzzle2_Reversa;
	PhysBody* Tp_Puzzle3_Reversa;

	bool Tp_1_Reversa = true;
	bool Tp_2_Reversa = true;
	bool Tp_3_Reversa = true;
	bool Tp_4_Reversa = true;
	bool Tp_5_Reversa = true;
	bool Tp_Jovani_Reversa = true;
	bool Tp_Puzzle_1_Reversa = true;
	bool Tp_Puzzle_2_Reversa = true;
	bool Tp_Puzzle_3_Reversa = true;
	bool Tp_Boss_Reversa = false;
};