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

	SDL_Texture* statsSheet;

	//Menu* menu = new Menu[4] { Menu::STATS, Menu::INVENTORY, Menu::SKILLS, Menu::EQUIPMENT };

};