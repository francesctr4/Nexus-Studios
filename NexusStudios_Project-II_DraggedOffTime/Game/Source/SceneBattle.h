#pragma once

#include "GuiManager.h"
#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"
#include "Animation.h"

struct SDL_Texture;

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

	int fx_sword_hit;

	//Combat turn
	int turn;

	//Variables a cambiar por las del player y las del enemigo
	
	int selected_player;
	int party_members;

	struct Party_Member {
		int HP;
		int max_HP;

		int DEF;
		int base_DEF;

		int DMG;
		int base_DMG;

		int buf_turns = 0;
	};

	Party_Member* m_players;
	/*std::array<Party_Member, 4> m_players;*/

	////Player 1
	//int p_HP = 100;
	//int p_max_HP = 100;
	//int p_DEF = 10;
	//int p_DMG = 20;

	////Player 2
	//int p2_HP = 250;
	//int p2_max_HP = 250;
	//int p2_DEF = 5;
	//int p2_DMG = 10;

	//Enemy
	int e_HP = 60;
	int e_max_HP = 60;
	int e_DEF = 10;
	int e_DMG = 20;
	int e_confusion_turns = 0;

	int enemy_last_action = NULL; // 0 => Attack // 1 => Defense

	//Sprite player (TODO)

	SDL_Texture* medievalInCombat;
	SDL_Texture* prehistoricInCombat;
	SDL_Texture* cyberpunkInCombat;
	SDL_Texture* apocalypseInCombat;

	Animation playerAnimation;
	Animation* currentAnimation;

	//Sprite enemy (TODO)

	SDL_Texture* enemyInCombat;
	Animation enemyAnimation;
	Animation* currentAnimationEnemy;

private:

	// Sprite Background

	SDL_Texture* background;

	//Sprites UI
	SDL_Texture* classID = nullptr;

	SDL_Texture* actionButtons = nullptr;

	SDL_Texture* lifeFrame = nullptr;

	SDL_Texture* healthBar = nullptr;

	SDL_Texture* selectionArrow = nullptr;

	SDL_Texture* playerSelection = nullptr;

	int action_selected = 0; 

	//GUI
	SDL_Texture* attackButton;
	GuiButton* AttackButton;

	SDL_Texture* defendButton;
	GuiButton* DefendButton;

	SDL_Texture* itemButton;
	GuiButton* ItemButton;

	// Variables para el control del QTE
	Timer qte_timer;
	int tolerance = 2; //Tolerancia en segundos
	int objetiveTime = 2; //Valor objetivo en ms
	bool qte = false;		//Definir si está en curso un quick time event

	int num_hits = 0;	//Numero de veces que se ha completado correctamente el quick time event
	int MAX_HITS = 3;

	//Timer - Variables
	Timer timer;
	bool timer_started = false;
	float delay = 0;

};