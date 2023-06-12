#pragma once

#include "GuiManager.h"
#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"
#include "Animation.h"
#include "Weapon.h"

struct SDL_Texture;

class SceneBattle : public Module
{
public:

	explicit SceneBattle(bool startEnabled);
	
	// Destructor
	virtual ~SceneBattle();

	bool Awake(pugi::xml_node& config) override;

	// Called before the first frame
	bool Start() override;

	// Called before all Updates
	bool PreUpdate() override;

	// Called each loop iteration
	bool Update(float dt) override;

	// Called after all Updates
	bool PostUpdate() override;

	// Called before quitting
	bool CleanUp() override;

	bool OnGuiMouseClickEvent(GuiControl* control) override;


public:

	bool enableMusic;

	// 10 FX in Battle

	uint fx_sword_hit;
	uint selectFX;
	uint healFX;
	uint skillFX;
	uint clawsFX;
	uint runFX;
	uint receiveHitFX;
	uint battleStartFX;
	uint failedToRunFX;
	uint enemyFailFX;

	//Combat turn
	int turn;

	int selected_player;

	struct Party_Member {
		int HP;
		int max_HP;

		int DEF;
		int base_DEF;

		int DMG;
		int base_DMG;

		int buf_turns = 0;
		int counter_turns = 0;
	};

	Party_Member* m_players;

	//Enemy
	int e_HP = 60;
	int e_max_HP = 60;
	int e_DEF = 10;
	int e_base_DEF = 10;
	int e_DMG = 20;
	int e_base_DMG = 20;
	int e_confusion_turns = 0;
	int e_buffed_turns = 0;

	int enemy_last_action = NULL; // 0 => Attack // 1 => Defense

	int boss = 0;	//Variable que controla si estás combatiendo con un boss (0 = No es boss, 1,2,3,4 = Nº del Boss)

	//Minion (Boss)
	bool minion = false;
	int m_HP = 60;
	int m_max_HP = 60;
	int m_DEF = 10;
	int m_DMG = 20;
	int m_confusion_turns = 0;

	//Sprite player (TODO)

	SDL_Texture* medievalInCombat;
	SDL_Texture* prehistoricInCombat;
	SDL_Texture* cyberpunkInCombat;
	SDL_Texture* apocalypseInCombat;

	Animation playerAnimation;
	Animation* currentAnimation;

	//Sprite enemy (TODO)

	SDL_Texture* enemyInCombat;
	Animation enemyAnimation32x32;
	Animation enemyAnimation64x32;
	Animation enemyAnimation32x64;
	Animation enemyAnimation64x64;
	Animation* currentAnimationEnemy;

	int widthEnemyCombat;
	int heightEnemyCombat;

	// Weapon Declaration

	Weapon rusticStoneAxe { WeaponEra::PREHISTORIC, WeaponType::MELEE, 50 };
	Weapon tribalLance { WeaponEra::PREHISTORIC, WeaponType::MID_RANGE, 50 };
	Weapon chiefsBow { WeaponEra::PREHISTORIC, WeaponType::LONG_RANGE, 50 };

	Weapon fallenBlade { WeaponEra::MEDIEVAL, WeaponType::MELEE, 50 };
	Weapon ascendantTwins { WeaponEra::MEDIEVAL, WeaponType::MID_RANGE, 50 };
	Weapon mrFlail { WeaponEra::MEDIEVAL, WeaponType::LONG_RANGE, 50 };

	Weapon chainsword { WeaponEra::CYBERPUNK, WeaponType::MELEE, 50 };
	Weapon uraniumshell { WeaponEra::CYBERPUNK, WeaponType::MID_RANGE, 50 };
	Weapon ionizedRifle { WeaponEra::CYBERPUNK, WeaponType::LONG_RANGE, 50 };

	Weapon graftedClaws { WeaponEra::APOCALYPSE, WeaponType::MELEE, 50 };
	Weapon agony { WeaponEra::APOCALYPSE, WeaponType::MID_RANGE, 50 };
	Weapon eyebull { WeaponEra::APOCALYPSE, WeaponType::LONG_RANGE, 50 };

	Weapon* equippedWeaponPrehistoric = &rusticStoneAxe;
	Weapon* equippedWeaponMedieval = &fallenBlade;
	Weapon* equippedWeaponCyberpunk = &chainsword;
	Weapon* equippedWeaponApocalypse = &graftedClaws;

private:

	// Sprite Background

	SDL_Texture* background;

	//Sprites UI
	SDL_Texture* classID = nullptr;

	SDL_Texture* actionButtons = nullptr;

	SDL_Texture* lifeFrame = nullptr;

	SDL_Texture* healthBar = nullptr;

	SDL_Texture* LArrow = nullptr;

	SDL_Texture* RArrow = nullptr;

	SDL_Texture* playerSelection = nullptr;

	SDL_Texture* q_sprite = nullptr;

	SDL_Texture* dialogue = nullptr;

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

	//Timer Texto de combate - Variables
	Timer combat_timmer;
	bool combat_timmer_started = false;
	bool show_battle_info = false;

	SDL_Rect arrow1;
	SDL_Rect arrow2;
};