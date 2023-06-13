#include "CombatManager.h"
#include "Player.h"
#include "Item.h"
#include "App.h"
#include "Textures.h"
#include "Input.h"
#include "SceneBattle.h"

#include "Defs.h"
#include "Log.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

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
int CombatManager:: NormalAttack(int p_DMG, int e_HP, int e_DEF) {
	
	// Timing is false

	int totalDamage;
	totalDamage = p_DMG - (e_DEF + enemy_increasedDefense);

	if (totalDamage < 0)
	{
		return e_HP - 5;
	}

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
	
	
};

int CombatManager::WeaponAttack(int p_DMG, int e_HP, int e_DEF, bool timing, int num_hits) {

	if (num_hits == 0)
	{
		return e_HP - 1;
	}
	
	if (timing)
	{
		//timing == true
		int totalDamage;
		totalDamage = (1.2 * p_DMG) - (e_DEF + enemy_increasedDefense);	//De momento va a ser el doble del daño del player si aciertas en timing

		if (totalDamage < 0)
		{
			return e_HP - 5 * num_hits;
		}

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
			return (e_HP - totalDamage * num_hits);
		}
	}
	else
	{
		//timing == false
		int totalDamage;
		totalDamage = (0.5 * p_DMG) - (e_DEF + enemy_increasedDefense);

		if (totalDamage < 0)
		{
			return e_HP - 5 * num_hits;
		}

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
			return (e_HP - totalDamage * num_hits);
		}
	}
};

void CombatManager::SkillAttack(int slected_player, int p_DMG, int p_DEF) {

	switch (slected_player) {
	case 0:	//Ranged - 360 No-scope (Dispara y ignora la defensa del enemigo)
		int totalDamage;
		totalDamage = p_DMG;
		app->sceneBattle->e_HP = app->sceneBattle->e_HP - totalDamage;
		if (totalDamage >= app->sceneBattle->e_HP)
		{
			enemy_increasedDefense = 0;
			//Kill enemy
			app->sceneBattle->e_HP = 0;
		}
		else
		{
			enemy_increasedDefense = 0;
			//Return amount of e_HP
			app->sceneBattle->e_HP = (app->sceneBattle->e_HP - totalDamage);
		}
		break;
	case 1:	//Tank - I’m the one who bonks! (Cada vez que el enemigo te ataque cuando esté activa esta variable, el enemigo recibirá daño al atacar)
		app->sceneBattle->m_players[slected_player].counter_turns = 2;
		break;
	case 2:	//Mage - Middle ages steroids (Sube levemente tus estadísticas durante 2 turnos (p_DMG y p_DEF)) p_buf_turns
		app->sceneBattle->m_players[slected_player].buf_turns = 2;
		app->sceneBattle->m_players[slected_player].DEF += 5;
		app->sceneBattle->m_players[slected_player].DMG += 10;
		break;
	case 3:	//Rogue - Ouroboros Sight (Añade "confusión" al enemigo que provoca que se ataque a sí mismo y le inflige algo de daño + p_HP se ve ligeramente reducido)
		app->sceneBattle->e_confusion_turns = 3;
		app->sceneBattle->e_HP -= 10;
		//Comprobar vida del enemy
		if (10 >= app->sceneBattle->e_HP)
		{
			enemy_increasedDefense = 0;
			//Kill enemy
			app->sceneBattle->e_HP = 0;
		}
		else
		{
			enemy_increasedDefense = 0;
			//Return amount of e_HP
			app->sceneBattle->e_HP -= 10;
		}

		//Comprobar vida del player
		if (5 >= app->sceneBattle->m_players[slected_player].HP)
		{
			//Kill player
			app->sceneBattle->m_players[slected_player].HP = 0;
		}
		else
		{
			app->sceneBattle->m_players[app->sceneBattle->selected_player].HP -= 5;
		}
		
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
		return 1;	// Cambiar a player 2
	}
	else if (selected_player == 1)
	{
		return 2;	// Cambiar a player 3
	}
	else if (selected_player == 2) { 

		return 3; // Cambiar a player 4

	}
	else if (selected_player == 3) {

		return 0; // Cambiar a player 1

	}
	else {

		return NULL;

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
	enemy_increasedDefense = 1; 
}

void CombatManager::AddMinion()
{
	if (app->sceneBattle->minion)
	{
		app->sceneBattle->m_HP = app->sceneBattle->m_max_HP;
	}
	else
	{
		app->sceneBattle->minion = true;
	}
}

void CombatManager::EnemyAttackAll(int e_DMG)
{
	for (int i = 0; i <= 4; i = i+1)
	{
		if ((app->sceneBattle->m_players[i].HP - e_DMG) > 0)
		{
			app->sceneBattle->m_players[i].HP = app->sceneBattle->m_players[i].HP - e_DMG;
		}
		else
		{
			app->sceneBattle->m_players[i].HP = 0;
		};
	}
	
}

void CombatManager::EnemyBuff(bool DMG, bool DEF)
{	
	app->sceneBattle->e_buffed_turns = 2;

	if (DEF)
	{
		//Subir defensa
		app->sceneBattle->e_DEF = app->sceneBattle->e_DEF + 5;
	}
	
	if (DMG)
	{
		//Subir daño
		app->sceneBattle->e_DMG = app->sceneBattle->e_DMG + 10;
	}
	
	
}
	
