#pragma once

#include "Timer.h"
#include "Physics.h"
#include <vector>

struct SDL_Texture;

class Medieval {
public:

	void Update();

	void TeleportMedieval();

	void TeleportMedievalReversa();

	void TeleportMedievalJovani();

public:

	PhysBody* TP_;

	bool Tp_;
};