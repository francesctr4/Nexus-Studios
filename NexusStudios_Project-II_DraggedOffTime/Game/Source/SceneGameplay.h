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
#include "Infierno.h"

#include "Puzzle1.h"
#include "Puzzle2.h"
#include "Puzzle3.h"

#include "Particle.h"
#include "ParticlePool.h"
#include "Emitter.h"
#include "Point.h"

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

	void LoadMapEntities(int map);
	
	void UnloadMapEntities();

	void LoadMap(int map);

public:

	bool enableMusic;

	pugi::xml_node xml_node;

	Player* player;


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

	uint endingScreenFX;

	Infierno mapa_Infierno;
	
	PhysBody* prova;

	// Particles

	Emitter* eWave_1 = nullptr;
	Emitter* eWave_2 = nullptr;
	Emitter* eBurst_1 = nullptr;
	Emitter* eBurst_2 = nullptr;

};