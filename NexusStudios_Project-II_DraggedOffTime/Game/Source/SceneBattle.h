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

		Weapon* equippedWeapon;

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

	/*Weapon* equippedWeaponPrehistoric = &rusticStoneAxe;
	Weapon* equippedWeaponMedieval = &fallenBlade;
	Weapon* equippedWeaponCyberpunk = &chainsword;
	Weapon* equippedWeaponApocalypse = &graftedClaws;*/

	// Weapon animations

	void WeaponAnimationDeclaration();

	float weaponIdleSpeed = 0.06f;

	Animation* currentAnimationWeapon;

	SDL_Texture* rusticStoneAxe_idle_tex;
	Animation rusticStoneAxe_idle;
	int rusticStoneAxe_idle_width = 288;
	int rusticStoneAxe_idle_height = 192;
	SDL_Texture* rusticStoneAxe_attack_tex;
	Animation rusticStoneAxe_attack;
	int rusticStoneAxe_attack_width = 480;
	int rusticStoneAxe_attack_height = 288;
	float rusticStoneAxe_attack_speed = 0.4f;

	SDL_Texture* tribalLance_idle_tex;
	Animation tribalLance_idle;
	int tribalLance_idle_width = 192;
	int tribalLance_idle_height = 288;
	SDL_Texture* tribalLance_attack_tex;
	Animation tribalLance_attack;
	int tribalLance_attack_width = 480;
	int tribalLance_attack_height = 288;
	float tribalLance_attack_speed = 0.4f;

	SDL_Texture* chiefsBow_idle_tex;
	Animation chiefsBow_idle;
	int chiefsBow_idle_width = 192;
	int chiefsBow_idle_height = 198;
	SDL_Texture* chiefsBow_attack_tex;
	Animation chiefsBow_attack;
	int chiefsBow_attack_width = 510;
	int chiefsBow_attack_height = 198;
	float chiefsBow_attack_speed = 0.4f;

	// -------------------------

	SDL_Texture* fallenBlade_idle_tex;
	Animation fallenBlade_idle;
	int fallenBlade_idle_width = 192;
	int fallenBlade_idle_height = 192;
	SDL_Texture* fallenBlade_attack_tex;
	Animation fallenBlade_attack;
	int fallenBlade_attack_width = 474;
	int fallenBlade_attack_height = 336;
	float fallenBlade_attack_speed = 0.4f;

	SDL_Texture* ascendantTwins_idle_tex;
	Animation ascendantTwins_idle;
	int ascendantTwins_idle_width = 192;
	int ascendantTwins_idle_height = 192;
	SDL_Texture* ascendantTwins_attack_tex;
	Animation ascendantTwins_attack;
	int ascendantTwins_attack_width = 1002;
	int ascendantTwins_attack_height = 282;
	float ascendantTwins_attack_speed = 0.4f;

	SDL_Texture* mrFlail_idle_tex;
	Animation mrFlail_idle;
	int mrFlail_idle_width = 192;
	int mrFlail_idle_height = 192;
	SDL_Texture* mrFlail_attack_tex;
	Animation mrFlail_attack;
	int mrFlail_attack_width = 0;
	int mrFlail_attack_height = 0;
	float mrFlail_attack_speed = 0.4f;

	// -------------------------

	SDL_Texture* chainsword_idle_tex;
	Animation chainsword_idle;
	int chainsword_idle_width = 288;
	int chainsword_idle_height = 216;
	SDL_Texture* chainsword_attack_tex;
	Animation chainsword_attack;
	int chainsword_attack_width = 540;
	int chainsword_attack_height = 390;
	float chainsword_attack_speed = 0.4f;

	SDL_Texture* uraniumshell_idle_tex;
	Animation uraniumshell_idle;
	int uraniumshell_idle_width = 192;
	int uraniumshell_idle_height = 192;
	SDL_Texture* uraniumshell_attack_tex;
	Animation uraniumshell_attack;
	int uraniumshell_attack_width = 480;
	int uraniumshell_attack_height = 204;
	float uraniumshell_attack_speed = 0.4f;

	SDL_Texture* ionizedRifle_idle_tex;
	Animation ionizedRifle_idle;
	int ionizedRifle_idle_width = 288;
	int ionizedRifle_idle_height = 192;
	SDL_Texture* ionizedRifle_attack_tex;
	Animation ionizedRifle_attack;
	int ionizedRifle_attack_width = 480;
	int ionizedRifle_attack_height = 234;
	float ionizedRifle_attack_speed = 0.4f;

	// -------------------------

	SDL_Texture* graftedClaws_idle_tex;
	Animation graftedClaws_idle;
	int graftedClaws_idle_width = 192;
	int graftedClaws_idle_height = 180;
	SDL_Texture* graftedClaws_attack_tex;
	Animation graftedClaws_attack;
	int graftedClaws_attack_width = 768;
	int graftedClaws_attack_height = 188;
	float graftedClaws_attack_speed = 0.4f;

	SDL_Texture* agony_idle_tex;
	Animation agony_idle;
	int agony_idle_width = 288;
	int agony_idle_height = 198;
	SDL_Texture* agony_attack_tex;
	Animation agony_attack;
	int agony_attack_width = 576;
	int agony_attack_height = 324;
	float agony_attack_speed = 0.4f;

	SDL_Texture* eyebull_idle_tex;
	Animation eyebull_idle;
	int eyebull_idle_width = 288;
	int eyebull_idle_height = 192;
	SDL_Texture* eyebull_attack_tex;
	Animation eyebull_attack;
	int eyebull_attack_width = 0;
	int eyebull_attack_height = 0;
	float eyebull_attack_speed = 0.4f;

	bool isAttacking = false;
	bool resetAnim = false;

	Timer timerWeaponAttack;

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

	SDL_Texture* Turn = nullptr;

	SDL_Texture* MedievalTurn = nullptr;

	SDL_Texture* PrehistoricalTurn = nullptr;

	SDL_Texture* CyberpunkTurn = nullptr;

	SDL_Texture* ApocalypseTurn = nullptr;

	SDL_Texture* EnemyTurn = nullptr;

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