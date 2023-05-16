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
#include "Timer.h"

#include "Puzzle1.h"
#include "Puzzle2.h"
#include "Puzzle3.h"

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

	void CheckEvent();

public:

	bool enableMusic;

	Player* player;
	bool map_selector = false;
	bool infierno = false;
	int actually = 0;

	/*SDL_Texture* Juan;
	Tween Juan_anim;*/

	std::vector<Enemy*> enemies;
	std::vector<Item*> items;
	std::vector<NPC*> npcs;

	// Menus

	FeatureMenu featureMenu;
	Pause pause;

	//Quests

	int r = 0; //Times you completed any mision
	
	//Triggers
	bool trigger_1 = false;
	int trigger_2 = 0;
	bool trigger_3 = false;

	//Misions completed
	bool first_mision = false;
	bool second_mision = false;
	bool third_mision = false;

	// Puzzles

	Puzzle1 puzzle1;
	Puzzle2 puzzle2;
	Puzzle3 puzzle3;

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
	
	bool Tp_0 = true;
	bool Tp_1 = true;
	bool Tp_2 = true;
	bool Tp_3 = true;
	bool Tp_4 = true;
	bool Tp_5 = true;
	bool Tp_Cofre = true;
	bool Tp_Jovani = true;
	bool Tp_Puzzle_1 = true;
	bool Tp_Puzzle_2 = true;
	bool Tp_Puzzle_3 = true;
	bool Tp_Boss = true;


};