#pragma once

#include "Timer.h"
#include "Physics.h"
#include <vector>

struct SDL_Texture;

class Lobby {
public:

	Lobby();

	virtual ~Lobby();

	void Start();

	void Update();

	void CleanUp();

	void TeleportLobby();

public:

	bool map_selector = false;


};