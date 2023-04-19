#pragma once

#include "GuiManager.h"
#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"
#include "Animation.h"

struct SDL_Texture;

struct Party_Member {
	int HP;
	int max_HP;
	int DEF;
	int DMG;
};

class SceneBattle : public Module
{
public:

	SceneBattle(bool startEnabled);
	
	// Destructor
	virtual ~SceneBattle();

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
	bool qte = false; //Quick Time Event 


	//Variables a cambiar por las del player y las del enemigo
	
	int selected_player;
	int party_members;

	//Player 1
	int p_HP = 100;
	int p_max_HP = 100;
	int p_DEF = 10;
	int p_DMG = 20;

	//Player 2
	int p2_HP = 250;
	int p2_max_HP = 250;
	int p2_DEF = 5;
	int p2_DMG = 10;

	//Enemy
	int e_HP = 60;
	int e_max_HP = 60;
	int e_DEF = 10;
	int e_DMG = 20;

private:

	//Sprite player (TODO)

	SDL_Texture* playerInCombat;
	Animation playerAnimation;
	Animation* currentAnimation;

	//Sprites UI
	SDL_Texture* classID = nullptr;

	SDL_Texture* actionButtons = nullptr;

	SDL_Texture* lifeFrame = nullptr;

	SDL_Texture* healthBar = nullptr;

	SDL_Texture* selectionArrow = nullptr;

	int action_selected = 0; 


	//GUI
	SDL_Texture* attackButton;
	GuiButton* AttackButton;

	SDL_Texture* defendButton;
	GuiButton* DefendButton;

	SDL_Texture* itemButton;
	GuiButton* ItemButton;


	// Variables para el control del QTE
	int startTime = 0;
	int endTime = NULL;
	int tolerance = 500; //Tolerancia en ms
	int objetiveTime = 100; //Valor objetivo en ms
};