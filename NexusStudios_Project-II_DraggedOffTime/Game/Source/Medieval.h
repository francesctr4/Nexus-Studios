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

	PhysBody* TP_Medieval_1;
	PhysBody* TP_Medieval_2;
	PhysBody* TP_Medieval_3;
	PhysBody* TP_Medieval_Jovani;
	PhysBody* TP_Medieval_5;
	PhysBody* TP_Medieval_6;
	PhysBody* TP_Medieval_Final;
	
	int a = 1;

	bool TP_Medieval_1_bool;
	bool TP_Medieval_2_bool;
	bool TP_Medieval_3_bool;
	bool TP_Medieval_Jovani_bool;
	bool TP_Medieval_5_bool;
	bool TP_Medieval_Final_bool;

	//Volver entre mapas
	PhysBody* TP_Medieval_1_Reversa;
	PhysBody* TP_Medieval_2_Reversa;
	PhysBody* TP_Medieval_3_Reversa;
	PhysBody* TP_Medieval_Jovani_Reversa;
	PhysBody* TP_Medieval_5_Reversa;
	PhysBody* TP_Medieval_Final_Reversa;

	bool TP_Medieval_1_bool_Reversa;
	bool TP_Medieval_2_bool_Reversa;
	bool TP_Medieval_3_bool_Reversa;
	bool TP_Medieval_Jovani_bool_Reversa;
	bool TP_Medieval_5_bool_Reversa;
	bool TP_Medieval_Final_bool_Reversa;
};