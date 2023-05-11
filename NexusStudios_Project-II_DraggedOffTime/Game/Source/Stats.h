#pragma once

struct SDL_Texture;

//enum class Menu {
//
//	STATS,
//	INVENTORY,
//	SKILLS,
//	EQUIPMENT
//
//};

class Stats {
public:

	void Load();

	void Update();

	void Draw();

public:

	bool statsEnabled;
	SDL_Texture* texture;

	int i;
	int j;
	int k;

	SDL_Texture* statsSheet;

	SDL_Texture* jambitaEstirada;

	SDL_Texture* inventory;

	SDL_Texture* skills;

	SDL_Texture* equipment;

	int e_characterSelector;
	int e_weaponSelector;

	//Menu* menu = new Menu[4] { Menu::STATS, Menu::INVENTORY, Menu::SKILLS, Menu::EQUIPMENT };

};