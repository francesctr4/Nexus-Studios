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
#include "SceneTitle.h"
#include "SceneGameplay.h"
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
	
	enableMusic = true;

	//Load textures
	classID = app->tex->Load("Assets/UI/ClassID.png");
	lifeFrame = app->tex->Load("Assets/UI/LifeFrame.png");
	actionButtons = app->tex->Load("Assets/UI/ActionButtons.png");
	healthBar = app->tex->Load("Assets/UI/HealthBar.png");

	/*attackButton = app->tex->Load("Assets/UI/Attack.png");
	SDL_Rect attack_rect = { 100, 500, 250, 108 };
	AttackButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 10, attackButton, "", attack_rect, this);

	defendButton = app->tex->Load("Assets/UI/Defend.png");
	SDL_Rect defend_rect = { 500, 500, 250, 108 };
	DefendButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 11, defendButton, "", defend_rect, this);

	itemButton = app->tex->Load("Assets/UI/Item.png");
	SDL_Rect item_rect = { 900, 500, 250, 108 };
	ItemButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 12, itemButton, "", item_rect, this);*/

	return true;
}

// Called each loop iteration
bool SceneBattle::PreUpdate()
{
	OPTICK_EVENT();

	app->entityManager->Disable();

	if (enableMusic) {

		app->audio->PlayMusic("Assets/Audio/Music/BattleTheme.ogg", 0);
		enableMusic = false;

	}

	return true;
}

// Called each loop iteration
bool SceneBattle::Update(float dt)
{
	OPTICK_EVENT();

	SDL_Rect rect = { 0,0, 1280, 720 };
	app->render->DrawRectangle(rect, 70, 80, 220, 150);

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
		//Standar actions
		if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
			app->sceneGameplay->player->godMode = !app->sceneGameplay->player->godMode;

		if (app->input->GetKey(SDL_SCANCODE_LEFT) == KEY_DOWN)
		{
			if (action_selected != 0)
			{
				action_selected--;

			}
			else if (action_selected == 0)
			{
				action_selected = 4;
			}
			
		}

		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		{
			
			if (action_selected != 4)
			{
				action_selected++;
			}
			else if (action_selected == 4)
			{
				action_selected = 0;
			}
		}

		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			switch (action_selected)
			{
			case 0: //Standar attack
				e_HP = app->combatManager->StandarAttack(p_DMG, e_HP, e_DEF);
				break;
			case 1:	//Quick time event attack (TODO)
				e_HP = app->combatManager->StandarAttack(p_DMG, e_HP, e_DEF);
				break;
			case 2: //Heal
				p_HP = app->combatManager->UseItem(p_HP);
				break;
			case 3: //Habilidades (TODO)
				e_HP = app->combatManager->StandarAttack(p_DMG, e_HP, e_DEF);
				break;
			case 4: //Run away
				if (app->combatManager->Run())
				{
					//Transition to Gameplay Screen
					app->fadeToBlack->Fade(this, (Module*)app->sceneGameplay);
				}
				else
				{
					LOG("You failed to run away");
				}
				break;
			}
			app->combatManager->playerTurn = !app->combatManager->playerTurn;
		}

		//Debug controls
		if (app->sceneGameplay->player->godMode)
		{
			if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
			{
				e_HP = app->combatManager->StandarAttack(p_DMG, e_HP, e_DEF);
				app->combatManager->playerTurn = !app->combatManager->playerTurn;
			}


			if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
			{
				e_HP = app->combatManager->StandarAttack(p_DMG, e_HP, e_DEF);
				app->combatManager->playerTurn = !app->combatManager->playerTurn;
				/*qte = true;
				startTime = SDL_GetTicks();*/
			}


			if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
			{
				app->combatManager->BlockAttack();
				app->combatManager->playerTurn = !app->combatManager->playerTurn;
			}


			if (app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
			{
				p_HP = app->combatManager->UseItem(p_HP);
				app->combatManager->playerTurn = !app->combatManager->playerTurn;
			}

			if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
			{
				if (app->combatManager->Run())
				{
					//Transition to Gameplay Screen
					app->fadeToBlack->Fade(this, (Module*)app->sceneGameplay);
				}
				else
				{
					LOG("You failed to run away");
					app->combatManager->playerTurn = !app->combatManager->playerTurn;
				}
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

			//Quick Time Event attack (Para la alpha)
			/*if (qte)
			{
				if (app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
				{
					endTime = SDL_GetTicks();
				}

				if (endTime != 0 && endTime - startTime >= (objetiveTime - tolerance) && endTime - startTime <= (objetiveTime + tolerance))
				{
					LOG("Ataque acertado");
					qte = false;
					app->combatManager->playerTurn = !app->combatManager->playerTurn;
				}

				if((!endTime - startTime >= (objetiveTime - tolerance) && endTime - startTime <= (objetiveTime + tolerance)))
				{
					LOG("Ataque fallido");
					qte = false;
					app->combatManager->playerTurn = !app->combatManager->playerTurn;
				}
			}*/
		}
	}
	else
	{
		
		//LOG("-------------ENEMY TURN-------------");
		int random_num = (rand() % 2) + 1;
		//LOG("Numero aleatorio %d", random_num);
		switch (random_num)
		{
		case 1:
			if (e_HP > 0)
			{
				p_HP = app->combatManager->EnemyAttack(e_DMG, p_HP, p_DEF);
				LOG("Atack");
				//Blit red color in screen
				app->render->DrawRectangle(rect, 255, 0, 0, 150);
			}
			break;
		case 2:
			if (e_HP > 0)
			{
				app->combatManager->EnemyBlockAttack();
				LOG("Defense");
				//Blit green color in screen
				app->render->DrawRectangle(rect, 0, 255, 0, 150);
			}
			break;
		default:
			break;
		}
		//LOG("-------------YOUR TURN-------------");
		
		app->combatManager->playerTurn = !app->combatManager->playerTurn;
		
	}

	//---

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) {

		enableMusic = true;
		app->fadeToBlack->Fade(this, (Module*)app->sceneLogo);

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
	
	//LOG("Player HP: %d", p_HP);
	//LOG("Enemy HP: %d", e_HP);

	// Enemy HP
	double e_percentage_life = (e_HP * 100.0) / e_max_HP;
	SDL_Rect rect_e = { 650, 40, 5 * e_percentage_life, 10 };
	app->render->DrawRectangle(rect_e, 70, 225, 20, 255);
	app->render->DrawText("Enemy HP:", 650, 30, 100, 20, { 255, 255, 255, 255 });
	std::string e_HP_string = std::to_string(e_HP);
	app->render->DrawText(e_HP_string, 650 + 125, 30, 25, 20, { 255, 255, 255, 255 });

	//Enemy sprite
	SDL_Rect enemy_sprite_rect = { 980-32, 420, 32, 32 };
	app->render->DrawRectangle(enemy_sprite_rect, 225, 30, 30, 255);

	// Player HP
	double p_percentage_life = (p_HP * 100.0) / p_max_HP;
	if (p_percentage_life < 50 && p_percentage_life >= 20)	//Yellow color
	{
		SDL_Rect rect_p = { 0, 20, 3 * p_percentage_life, 20 };
		app->render->DrawTexture(healthBar, 80, 30, &rect_p);
	}
	if (p_percentage_life < 20) //Red color
	{
		SDL_Rect rect_p = { 0, 40, 3 * p_percentage_life, 20 };
		app->render->DrawTexture(healthBar, 80, 30, &rect_p);
	}
	if (p_percentage_life >= 50) //Green color
	{
		SDL_Rect rect_p = { 0, 0, 3 * p_percentage_life, 20 };
		app->render->DrawTexture(healthBar, 80, 30, &rect_p);
	}
	app->render->DrawText("Player HP:", 80, 10, 100, 20, { 255, 255, 255, 255 });
	std::string p_HP_string = std::to_string(p_HP);
	app->render->DrawText(p_HP_string, 80 + 125, 10, 25, 20, { 255, 255, 255, 255 });

	//Player sprite
	SDL_Rect player_sprite_rect = { 300, 420, 32, 32 };
	app->render->DrawRectangle(player_sprite_rect, 180, 125, 230, 255);

	if (app->sceneGameplay->player->godMode)
	{
		// Combat UI - Controls (Debug)
		app->render->DrawText("1 - Standar Attack", 100, 100, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("2 - Quick Time Event Attack", 100, 115, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("3 - Defend (Block)", 100, 130, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("4 - Use Item", 100, 145, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("5 - Run away", 100, 160, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("6 - Enemy Attack", 100, 175, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("7 - Enemy Defense", 100, 190, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("TAB - Skip Turn", 100, 205, 100, 20, { 255, 255, 255, 255 });
	}

	//Combat UI - Visual
	app->render->DrawTexture(classID, 20, 20); 
	app->render->DrawTexture(lifeFrame, 80, 30);
	//Atcion selector
	SDL_Rect actionSelector_rect = { action_selected * 70, 0, 70, 70};
	app->render->DrawTexture(actionButtons, 235, 305, &actionSelector_rect);

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