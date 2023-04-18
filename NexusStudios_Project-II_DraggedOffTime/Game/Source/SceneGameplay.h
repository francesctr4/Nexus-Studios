#pragma once

#include "Player.h"
#include "NPC.h"
#include "Enemy.h"

struct SDL_Texture;

class SceneGameplay : public Module
{
public:

	SceneGameplay(bool startEnabled);

	// Destructor
	virtual ~SceneGameplay();

	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control);

public:

	bool enableMusic;

public:

	Player* player;
	bool map_selector = false;
	int actually = 0;

	List<Enemy*> enemies;

};