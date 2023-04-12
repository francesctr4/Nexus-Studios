#include "App.h"
#include "Defs.h"
#include "Log.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "CombatManager.h"
#include <ctime>

#include "SceneBattle.h"

SceneBattle::SceneBattle()
{
	name.Create("sceneEnding");
}

// Destructor
SceneBattle::~SceneBattle()
{}

// Called before the first frame
bool SceneBattle::Start()
{

	return true;
}

// Called each loop iteration
bool SceneBattle::PreUpdate()
{
	OPTICK_EVENT();

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

	if (p_HP == 0 || e_HP == 0)
	{
		//End combat
		TransitionToScene(SceneType::LOGO);

	}

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

		TransitionToScene(SceneType::LOGO);

	}

	
	//SDL_Rect rect = { 0,0, 1280, 720 };
	//app->render->DrawRectangle(rect, 0, 0, 255, 150);
	

	return true;
}

// Called each loop iteration
bool SceneBattle::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;
	
	LOG("Player HP: %d", p_HP);
	LOG("Enemy HP: %d", e_HP);

	// Enemy HP
	SDL_Rect rect_e = { 0, 40*2, e_HP * 2, 10 };
	app->render->DrawRectangle(rect_e, 10, 255, 10, 255);
	app->render->DrawText("Enemy HP:", 0, 30*2, 100, 20, { 255, 255, 255, 255 });

	// Player HP
	SDL_Rect rect_p = { 0, 40, p_HP * 2, 10 };
	app->render->DrawRectangle(rect_p, 10, 255, 10, 255);
	app->render->DrawText("Player HP:", 0, 30, 100, 20, { 255, 255, 255, 255 });

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