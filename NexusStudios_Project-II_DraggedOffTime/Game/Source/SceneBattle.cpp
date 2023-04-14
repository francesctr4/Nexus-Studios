#include "App.h"
#include "Defs.h"
#include "Log.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "FadeToBlack.h"
#include "CombatManager.h"
#include "EntityManager.h"
#include <ctime>

#include "SceneBattle.h"

SceneBattle::SceneBattle(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneEnding");
}

// Destructor
SceneBattle::~SceneBattle()
{}

bool SceneBattle::Awake(pugi::xml_node& config)
{

	return true;
}

// Called before the first frame
bool SceneBattle::Start()
{

	return true;
}

// Called each loop iteration
bool SceneBattle::PreUpdate()
{
	OPTICK_EVENT();

	app->entityManager->Disable();

	return true;
}

// Called each loop iteration
bool SceneBattle::Update(float dt)
{
	OPTICK_EVENT();

	SDL_Rect rect = { 0,0, 1280, 720 };
	app->render->DrawRectangle(rect, 0, 0, 255, 150);

	//Random number generator
	srand(time(NULL));

	//Manage Combat (Turn Handler)

	//if (p_HP == 0 || e_HP == 0)
	//{
	//	//End combat
	//	TransitionToScene(SceneType::LOGO);

	//}

	if (app->combatManager->playerTurn)
	{
		if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			e_HP = app->combatManager->StandarAttack(p_DMG, e_HP, e_DEF);
			app->combatManager->playerTurn = !app->combatManager->playerTurn;
		}
			

		if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			e_HP = app->combatManager->TimeEventAttack(p_DMG, e_HP, e_DEF);
			app->combatManager->playerTurn = !app->combatManager->playerTurn;
		}
			

		if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		{
			app->combatManager->BlockAttack();
			app->combatManager->playerTurn = !app->combatManager->playerTurn;
		}
			

		if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		{
			app->combatManager->UseItem();
			app->combatManager->playerTurn = !app->combatManager->playerTurn;
		}
			

		if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		{
			p_HP = app->combatManager->EnemyAttack(e_DMG, p_HP, p_DEF);
			app->combatManager->playerTurn = !app->combatManager->playerTurn;
		}
			

		if (app->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
		{
			app->combatManager->EnemyBlockAttack();
			app->combatManager->playerTurn = !app->combatManager->playerTurn;
		}
			

		if (app->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
			app->combatManager->playerTurn = !app->combatManager->playerTurn;
	}
	else
	{
		LOG("-------------ENEMY TURN-------------");
		int random_num = (rand() % 2) + 1;
		LOG("Numero aleatorio %d", random_num);
		switch (random_num)
		{
		case 1:
			p_HP = app->combatManager->EnemyAttack(e_DMG, p_HP, p_DEF);
			LOG("Atack");
			//Blit red color in screen
			app->render->DrawRectangle(rect, 255, 0, 0, 150);
			break;
		case 2:
			app->combatManager->EnemyBlockAttack();
			LOG("Defense");
			//Blit green color in screen
			app->render->DrawRectangle(rect, 0, 255, 0, 150);
			
			break;
		default:
			break;
		}
		LOG("-------------YOUR TURN-------------");
		app->combatManager->playerTurn = !app->combatManager->playerTurn;
	}

	//---

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {

		//TransitionToScene(SceneType::LOGO);
		app->fadeToBlack->Fade(this, (Module*)app->sceneLogo);
	}

	
	//SDL_Rect rect = { 0,0, 1280, 720 };
	//app->render->DrawRectangle(rect, 0, 0, 255, 150);
	
	LOG("Player HP: %d", p_HP);
	LOG("Enemy HP: %d", e_HP);

	// Enemy HP
	double e_percentage_life = (e_HP * 100.0) / e_max_HP;
	SDL_Rect rect_e = { 650, 40, 5 * e_percentage_life, 10 };
	app->render->DrawRectangle(rect_e, 10, 255, 10, 255);
	app->render->DrawText("Enemy HP:", 650, 30, 100, 20, { 255, 255, 255, 255 });
	std::string e_HP_string = std::to_string(e_HP);
	app->render->DrawText(e_HP_string, 650 + 125, 30, 25, 20, { 255, 255, 255, 255 });

	//Enemy sprite


	// Player HP
	double p_percentage_life = (p_HP * 100.0) / p_max_HP;
	SDL_Rect rect_p = { 0, 40, 5 * p_percentage_life, 10 };
	app->render->DrawRectangle(rect_p, 10, 255, 10, 255);
	app->render->DrawText("Player HP:", 0, 30, 100, 20, { 255, 255, 255, 255 });
	std::string p_HP_string = std::to_string(p_HP);
	app->render->DrawText(p_HP_string, 0 + 125, 30, 25, 20, { 255, 255, 255, 255 });

	//Player sprite


	// Combat UI - Controls
	app->render->DrawText("1 - Standar Attack", 0, 100, 100, 20, { 255, 255, 255, 255 });
	app->render->DrawText("2 - Quick Time Event Attack", 0, 115, 100, 20, { 255, 255, 255, 255 });
	app->render->DrawText("3 - Defend (+DEF)", 0, 130, 100, 20, { 255, 255, 255, 255 });
	app->render->DrawText("4 - Use Item", 0, 145, 100, 20, { 255, 255, 255, 255 });
	app->render->DrawText("-------------------", 0, 160, 100, 20, { 255, 255, 255, 255 });
	app->render->DrawText("5 - Enemy Attack", 0, 175, 100, 20, { 255, 255, 255, 255 });
	app->render->DrawText("6 - Enemy Defense", 0, 190, 100, 20, { 255, 255, 255, 255 });
	app->render->DrawText("TAB - Skip Turn", 0, 205, 100, 20, { 255, 255, 255, 255 });

	return true;
}

// Called each loop iteration
bool SceneBattle::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;
	


	return true;
}

// Called before quitting
bool SceneBattle::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool SceneBattle::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}