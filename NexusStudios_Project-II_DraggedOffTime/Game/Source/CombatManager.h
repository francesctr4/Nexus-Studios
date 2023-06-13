#ifndef __COMBATMANAGER_H__
#define __COMBATMANAGER_H__

#include "Module.h"
#include "List.h"
#include "SString.h"
#include "Weapon.h"

struct QTE {
	int startTime; //tiempo objetivo en milisegundos
	int duration; //duración del QTE en milisegundos
	int timeTolerance; //tolerancia de tiempo permitido para el jugador en milisegundos
};

class CombatManager : public Module
{
public:

	explicit CombatManager(bool startEnabled);

	// Destructor
	virtual ~CombatManager();

	// Called before render is available
	bool Awake(pugi::xml_node&) override;

	// Called after Awake
	bool Start() override;

	// Called every frame
	bool Update(float dt) override;

	// Called before quitting
	bool CleanUp() override;

	// Combat handler fuction
	//void Combat(int p_HP, int p_DEF, int p_DMG, int e_HP, int e_DEF, int e_DMG);


	//Combat Fuctions
	
	//1.Deal standar attack (Return e_HP)
	int NormalAttack(int p_DMG, int e_HP, int e_DEF);

	//2.Deal Quick time event attack (Return e_HP)
	int WeaponAttack(int p_DMG, int e_HP, int e_DEF, bool timing, int num_hits);

	//3.Skill attack
	void SkillAttack(int slected_player, int p_DMG, int p_DEF);

	//4.Use an item in combat - Heal (Returns p_HP)
	int UseItem(int p_HP);

	//5.Run from the battle
	bool Run();

	//6.Change player
	int ChangeParty(int selected_player);

	//7.Enemy attack (Return p_HP)
	int EnemyAttack(int e_DMG, int p_HP, int p_DEF);

	//8.Enemy blocks attack
	void EnemyBlockAttack();

	//9.Enemy invokes a minion
	void AddMinion();

	//10.Enemy attack to all
	void EnemyAttackAll(int e_DMG);

	//11.Enemy buff stats
	void EnemyBuff(bool DMG, bool DEF);

	//12.Change Weapon
	void ChangeWeapon(int player_selected, Weapon* arma);

public:

	bool playerTurn = true;

	//Player defense
	int increasedDefense = 0;

	//Enemy defense
	int enemy_increasedDefense = 0;

};

#endif // __COMBATMANAGER_H__
