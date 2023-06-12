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
	//Avanzar entre mapas
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

	//Volver entre mapas
	PhysBody* TP_Prehistoria_1_Reversa;
	PhysBody* TP_Prehistoria_2_Reversa;
	PhysBody* TP_Prehistoria_3_Reversa;
	PhysBody* TP_Prehistoria_Jovani_Reversa;
	PhysBody* TP_Prehistoria_5_Reversa;
	PhysBody* TP_Prehistoria_Final_Reversa;

	bool TP_Prehistoria_1_bool_Reversa;
	bool TP_Prehistoria_2_bool_Reversa;
	bool TP_Prehistoria_3_bool_Reversa;
	bool TP_Prehistoria_Jovani_bool_Reversa;
	bool TP_Prehistoria_5_bool_Reversa;
	bool TP_Prehistoria_Final_bool_Reversa;
};