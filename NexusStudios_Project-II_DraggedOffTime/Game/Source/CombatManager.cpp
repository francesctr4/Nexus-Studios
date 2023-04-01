#include "CombatManager.h"
#include "Player.h"
#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Scene.h"
#include "Input.h"

#include "Defs.h"
#include "Log.h"




CombatManager::CombatManager(bool startEnabled) : Module(startEnabled)
{
	name.Create("CombatManager");
}

// Destructor
CombatManager::~CombatManager()
{}

// Called before render is available
bool CombatManager::Awake(pugi::xml_node& config)
{
	LOG("Loading CombatManager");
	bool ret = true;

	return ret;
}

bool CombatManager::Start() {

	bool ret = true;


	return ret;
}

// Called before quitting
bool CombatManager::CleanUp()
{
	bool ret = true;
	

	return ret;
}


bool CombatManager::Update(float dt)
{
	OPTICK_EVENT();
	bool ret = true;
	

	return ret;
}

//Player actions
int CombatManager::StandarAttack(int p_DMG, int e_HP, int e_DEF) {
	
	int totalDamage;
	totalDamage = p_DMG - (e_DEF + enemy_increasedDefense);

	if (totalDamage > e_HP)
	{
		enemy_increasedDefense = 0;
		//Kill enemy
		return 0;
	}
	else
	{
		enemy_increasedDefense = 0;
		//Return amount of e_HP
		return e_HP - totalDamage;
	}
};

int CombatManager::TimeEventAttack(int p_DMG, int e_HP, int e_DEF) {
	//De momento nada, se incluirá en la siguiente versión
	return 0;
};

void CombatManager::BlockAttack() {

	//Add X ammout of DEF to the player for the next turn
	increasedDefense = 10; //10 is a placeholder
};

void CombatManager::UseItem() {

};


//Enemy actions
int CombatManager::EnemyAttack(int e_DMG, int p_HP, int p_DEF) {

	int totalDamage;
	totalDamage = e_DMG - (p_DEF + increasedDefense);

	if (totalDamage > p_HP)
	{
		increasedDefense = 0;
		//Kill player
		return 0;
	}
	else
	{
		increasedDefense = 0;
		//Return amount of p_HP
		return p_HP - totalDamage;
	}
}

void CombatManager::EnemyBlockAttack() {

	//Add X ammout of DEF to the enemy for the next turn
	enemy_increasedDefense = 10; //10 is a placeholder
}

