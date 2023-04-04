#ifndef __COMBATMANAGER_H__
#define __COMBATMANAGER_H__

#include "Module.h"
#include "List.h"
#include "SString.h"


class CombatManager : public Module
{
public:

	CombatManager(bool startEnabled);

	// Destructor
	virtual ~CombatManager();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called after Awake
	bool Start();

	// Called every frame
	bool Update(float dt);

	// Called before quitting
	bool CleanUp();

	// Combat handler fuction
	//void Combat(int p_HP, int p_DEF, int p_DMG, int e_HP, int e_DEF, int e_DMG);

	//Combat Fuctions
	
	//1.Deal standar attack (Return e_HP)
	int StandarAttack(int p_DMG, int e_HP, int e_DEF);

	//2.Deal Quick time event attack (Return e_HP)
	int TimeEventAttack(int p_DMG, int e_HP, int e_DEF);

	//3.Block enemy attack (= increase your defende one turn)
	void BlockAttack();

	//4.Use an item in combat
	void UseItem();

	//5.Enemy attack (Return p_HP)
	int EnemyAttack(int e_DMG, int p_HP, int p_DEF);

	//6.Enemy blocks attack
	void EnemyBlockAttack();





public:

	bool playerTurn = true;

	//Player defense
	int increasedDefense = 0;

	//Enemy defense
	int enemy_increasedDefense = 0;

};

#endif // __COMBATMANAGER_H__
