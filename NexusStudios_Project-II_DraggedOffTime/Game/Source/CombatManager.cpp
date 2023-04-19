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

int CombatManager::UseItem(int p_HP) {
	if (p_HP + 25 > app->sceneBattle->p_max_HP)
	{
		return app->sceneBattle->p_max_HP;
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
	enemy_increasedDefense = 10; //10 is a placeholder
}


//int CombatManager::QuickTimeEvent() {
//	// Tiempo objetivo en milisegundos
//	int objectiveTime = 500;
//
//	// Variables para el control del QTE
//	bool qteStarted = false;
//	bool completed = false;
//	int startTime = 0;
//	int endTime = 0;
//
//	// Bucle principal del QTE
//	while (true) {
//		// Comprobar si el usuario ha iniciado el QTE
//		if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN) {
//			qteStarted = true;
//			startTime = SDL_GetTicks();
//		}
//
//		// Salir del bucle si el QTE ha terminado
//		if (completed || SDL_GetTicks() - startTime >= objectiveTime) {
//			break;
//		}
//
//		// Comprobar si el usuario ha completado el QTE
//		if (qteStarted && app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) {
//			completed = true;
//			endTime = SDL_GetTicks();
//		}
//
//		// Dibujar el QTE
//		SDL_SetRenderDrawColor(app->render->renderer, 0, 0, 255, 255);
//		SDL_Rect rect = { 100, 100, 100, 100 };
//		SDL_RenderFillRect(app->render->renderer, &rect);
//		SDL_RenderPresent(app->render->renderer);
//	}
//
//	// Devolver la cantidad de milisegundos que ha y de diferencia entre el tiempo objetivo y el input del jugador
//	if (completed) {
//		LOG("Resultado: %f", endTime - startTime);
//		return endTime - startTime;		
//	}
//	else {
//		LOG("Resultado: %f", objectiveTime);
//		return objectiveTime;
//	}
//}