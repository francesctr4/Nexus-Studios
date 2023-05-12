#pragma once

#include "Player.h"
#include "NPC.h"
#include "Enemy.h"
#include "Item.h"
#include "GuiManager.h"
#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"
#include "FeatureMenu.h"
#include "Pause.h"
#include "Tweening.h"

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

	Player* player;
	bool map_selector = false;
	int actually = 0;

	SDL_Texture* Juan;
	Tween Juan_anim;

	List<Enemy*> enemies;
	List<NPC*> npcs;

	// Menus

	FeatureMenu featureMenu;
	Pause pause;

};