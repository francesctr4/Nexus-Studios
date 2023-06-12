#pragma once

#include "Timer.h"
#include "Physics.h"
#include <vector>

struct SDL_Texture;

class Prehistoria {
public:

	void Update();

	void TeleportPrehistoria();
	void TeleportPrehistoriaJovani();
	
	void TeleportPrehistoria_Revers();

public:

	PhysBody* TP_Prehistoria_1;
	PhysBody* TP_Prehistoria_2;
	PhysBody* TP_Prehistoria_3;
	PhysBody* TP_Prehistoria_Jovani;
	PhysBody* TP_Prehistoria_5;
	PhysBody* TP_Prehistoria_Final;

	bool TP_Prehistoria_1_bool;
	bool TP_Prehistoria_2_bool;
	bool TP_Prehistoria_3_bool;
	bool TP_Prehistoria_Jovani_bool;
	bool TP_Prehistoria_5_bool;
	bool TP_Prehistoria_Final_bool;
};