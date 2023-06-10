#pragma once

#include "Timer.h"
#include "Physics.h"
#include <vector>

struct SDL_Texture;

class Lobby {
public:

	void Update();

	void TeleportLobby();

public:

	PhysBody* Tp_Lobby_1;
	PhysBody* Tp_Lobby_Infierno;
	PhysBody* Tp_Lobby_Medieval;
	PhysBody* Tp_Lobby_Prehistoria;

};