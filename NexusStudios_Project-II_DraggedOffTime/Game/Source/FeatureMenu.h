#pragma once

#include "Animation.h"
#include "Inventory.h"
#include "GuiManager.h"
#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"

struct SDL_Texture;

//enum class Menu {
//
//	STATS,
//	INVENTORY,
//	SKILLS,
//	EQUIPMENT
//
//};

class FeatureMenu {
public:

	void Load();

	void Update();

	void PostUpdate();

public:

	//Visuals

	SDL_Texture* Fondo;

	SDL_Texture* stats;
	GuiButton* Stats;

	SDL_Texture* inventory_;
	GuiButton* Inventory_;

	SDL_Texture* equipment;
	GuiButton* Equipment;

	SDL_Texture* skills;
	GuiButton* Skills;

	SDL_Texture* quests;
	GuiButton* Quests;

	//Characters

	bool ChangeCharacters;

	SDL_Texture* medieval;
	GuiButton* Medieval;

	SDL_Texture* prehistorical;
	GuiButton* Prehistorical;

	SDL_Texture* cyberpunk;
	GuiButton* Cyberpunk;

	SDL_Texture* apocalypse;
	GuiButton* Apocalypse;

	//SFX
	uint OpenPause;
	uint ClosePause;

	//Textures

	SDL_Texture* Stats_visual;

	SDL_Texture* Inventory_visual;


	bool statsEnabled;
	SDL_Texture* texture;

	int i;
	int j;
	int k;
	int l;

	// ---------------------------------

	SDL_Texture* kleosMedieval;
	SDL_Texture* kleosPrehistoric;
	SDL_Texture* kleosCyberpunk;
	SDL_Texture* kleosApocalypse;

	Animation* currentAnimation;
	Animation KleosIdle;

	// ---------------------------------

	//SDL_Texture* statsSheet;

	//SDL_Texture* jambitaEstirada;

	//SDL_Texture* inventory;

	//SDL_Texture* skills;

	//SDL_Texture* equipment;

	//SDL_Texture* quests;

	int e_characterSelector;
	int e_weaponSelector;

	//Menu* menu = new Menu[4] { Menu::STATS, Menu::INVENTORY, Menu::SKILLS, Menu::EQUIPMENT };
	
	// Inventory

	Inventory inventoryManager;

};