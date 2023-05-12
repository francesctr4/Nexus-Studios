#pragma once

#include "Animation.h"
#include "Inventory.h"

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

	SDL_Texture* statsSheet;

	SDL_Texture* jambitaEstirada;

	SDL_Texture* inventory;

	SDL_Texture* skills;

	SDL_Texture* equipment;

	SDL_Texture* quests;

	int e_characterSelector;
	int e_weaponSelector;

	//Menu* menu = new Menu[4] { Menu::STATS, Menu::INVENTORY, Menu::SKILLS, Menu::EQUIPMENT };
	
	//

	Inventory inventoryManager;

};