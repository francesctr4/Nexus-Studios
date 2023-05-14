#include "CombatManager.h"
#include "Player.h"
#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Input.h"
#include "SceneBattle.h"

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
int CombatManager:: NormalAttack(int p_DMG, int e_HP, int e_DEF, bool timing, int num_hits) {
	
	if (timing)
	{
		LOG("Good Timing");	//timing == true
		int totalDamage;
		totalDamage = (p_DMG - (e_DEF + enemy_increasedDefense)) * num_hits;	//De momento va a ser el doble del daño del player si aciertas en timing

		if (totalDamage >= e_HP)
		{
			enemy_increasedDefense = 0;
			//Kill enemy
			return 0;
		}
		else
		{
			enemy_increasedDefense = 0;
			//Return amount of e_HP
			return (e_HP - totalDamage);
		}
	}
	else
	{
		LOG("Bad Timing");	//timing == false
		int totalDamage;
		totalDamage = (0.5 * p_DMG - (e_DEF + enemy_increasedDefense)) * num_hits;

		if (totalDamage >= e_HP)
		{
			enemy_increasedDefense = 0;
			//Kill enemy
			return 0;
		}
		else
		{
			enemy_increasedDefense = 0;
			//Return amount of e_HP
			return (e_HP - totalDamage);
		}
	}
	
};

int CombatManager::WeaponAttack(int p_DMG, int e_HP, int e_DEF, bool timing, int num_hits) {
	//De momento nada, se incluirá en la siguiente versión
	
	if (timing)
	{
		LOG("Good Timing");	//timing == true
		int totalDamage;
		totalDamage = (1.2 * p_DMG - (e_DEF + enemy_increasedDefense)) * num_hits;	//De momento va a ser el doble del daño del player si aciertas en timing

		if (totalDamage >= e_HP)
		{
			enemy_increasedDefense = 0;
			//Kill enemy
			return 0;
		}
		else
		{
			enemy_increasedDefense = 0;
			//Return amount of e_HP
			return (e_HP - totalDamage);
		}
	}
	else
	{
		LOG("Bad Timing");	//timing == false
		int totalDamage;
		totalDamage = (0.75 * p_DMG - (e_DEF + enemy_increasedDefense)) * num_hits;

		if (totalDamage >= e_HP)
		{
			enemy_increasedDefense = 0;
			//Kill enemy
			return 0;
		}
		else
		{
			enemy_increasedDefense = 0;
			//Return amount of e_HP
			return (e_HP - totalDamage);
		}
	}
};

int CombatManager::SkillAttack(int slected_player) {

	switch (slected_player) {
	case 0:

		break;
	case 1:

		break;
	case 2:

		break;
	case 3:

		break;
	}
};

int CombatManager::UseItem(int p_HP) {
	if (p_HP + 25 > app->sceneBattle->m_players[app->sceneBattle->selected_player].max_HP)
	{
		return app->sceneBattle->m_players[app->sceneBattle->selected_player].max_HP;
	}
	else
	{
		return p_HP + 25; //25 como valor provisional
	}
	
	
	
};

bool CombatManager::Run() {
	int numeroAleatorio = rand() % 100;
	if (numeroAleatorio <= 65) { //65% de probalidades de escapar
		return true;
	}
	else {
		return false;
	}
};

int CombatManager::ChangeParty(int selected_player) {
	if (selected_player  == 0)
	{
		return 1;	//Cambiar a player 2
	}
	else if (selected_player == 1)
	{
		return 0;	//Cambiar a player 1
	}
};

//Enemy actions
int CombatManager::EnemyAttack(int e_DMG, int p_HP, int p_DEF) {

	int totalDamage;
	totalDamage = e_DMG - (p_DEF + increasedDefense);

	if (totalDamage < 0)
	{
		return 0;
	}

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
	enemy_increasedDefense = 5; //5 is a placeholder
}
