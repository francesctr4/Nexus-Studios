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

	for (int i = 0; i < 4; i++) {

		playerAnimation.PushBack({ 177 * (0 + i), 177 * 0, 177, 177 });

	}
	playerAnimation.loop = true;
	playerAnimation.speed = 0.06f;

	for (int i = 3; i >= 0; i--) {

		enemyAnimation.PushBack({ 115 * (0 + i), 115 * 0, 115, 115 });

	}
	enemyAnimation.loop = true;
	enemyAnimation.speed = 0.06f;


	return true;
}

// Called before the first frame
bool SceneBattle::Start()
{
	//Cambiar para despu�s de la vertical slice
	party_members = 2;
	selected_player = 0;
	turn = 0;

	m_players = new Party_Member[4] { {100, 100, 10, 20}, {150, 150, 10, 30}, {200, 200, 10, 40}, {200, 200, 10, 40} };

	enableMusic = true;

	//Load textures
	classID = app->tex->Load("Assets/UI/ClassID.png");
	lifeFrame = app->tex->Load("Assets/UI/LifeFrame.png");
	actionButtons = app->tex->Load("Assets/UI/ActionButtons.png");
	healthBar = app->tex->Load("Assets/UI/HealthBar.png");
	selectionArrow = app->tex->Load("Assets/UI/SelectionArrow.png");
	playerSelection = app->tex->Load("Assets/UI/PlayerSelector.png");

	//Load audios
	fx_sword_hit = app->audio->LoadFx("Assets/Audio/FX/SwordFX.wav");

	action_selected = 0;

	/*attackButton = app->tex->Load("Assets/UI/Attack.png");
	SDL_Rect attack_rect = { 100, 500, 250, 108 };
	AttackButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 10, attackButton, "", attack_rect, this);

	defendButton = app->tex->Load("Assets/UI/Defend.png");
	SDL_Rect defend_rect = { 500, 500, 250, 108 };
	DefendButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 11, defendButton, "", defend_rect, this);

	itemButton = app->tex->Load("Assets/UI/Item.png");
	SDL_Rect item_rect = { 900, 500, 250, 108 };
	ItemButton = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 12, itemButton, "", item_rect, this);*/

	// Player texture

	currentAnimation = &playerAnimation;

	playerInCombat = app->tex->Load("Assets/Textures/PlayerInCombat.png");
	playerInCombat2 = app->tex->Load("Assets/Textures/PlayerInCombat2.png");

	// Enemy texture

	currentAnimationEnemy = &enemyAnimation;

	background = app->tex->Load("Assets/Textures/BattleBackground.png");

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
				action_selected = 5;
			}
			
		}

		if (app->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_DOWN)
		{
			
			if (action_selected != 5)
			{
				action_selected++;
			}
			else if (action_selected == 5)
			{
				action_selected = 0;
			}
		}

		if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			switch (action_selected)
			{
			case 0: //Standar attack
				e_HP = app->combatManager->StandarAttack(m_players[selected_player].DMG, e_HP, e_DEF);
				app->audio->PlayFx(fx_sword_hit);
				break;
			case 1:	//Quick time event attack (TODO)
				e_HP = app->combatManager->StandarAttack(m_players[selected_player].DMG, e_HP, e_DEF);
				app->audio->PlayFx(fx_sword_hit);
				break;
			case 2: //Heal
				m_players[selected_player].HP = app->combatManager->UseItem(m_players[selected_player].HP);
				break;
			case 3: //Habilidades (TODO)
				e_HP = app->combatManager->StandarAttack(m_players[selected_player].DMG, e_HP, e_DEF);
				app->audio->PlayFx(fx_sword_hit);
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
			case 5:
				selected_player = app->combatManager->ChangeParty(selected_player);
				break;
			}
			app->combatManager->playerTurn = !app->combatManager->playerTurn;
		}

		//Debug controls
		if (app->sceneGameplay->player->godMode)
		{
			if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
			{
				e_HP = app->combatManager->StandarAttack(m_players[selected_player].DMG, e_HP, e_DEF);
				app->combatManager->playerTurn = !app->combatManager->playerTurn;
			}


			if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
			{
				e_HP = app->combatManager->StandarAttack(m_players[selected_player].DMG, e_HP, e_DEF);
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
				m_players[selected_player].HP = app->combatManager->UseItem(m_players[selected_player].HP);
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

			if (app->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
			{
				selected_player = app->combatManager->ChangeParty(selected_player);
				app->combatManager->playerTurn = !app->combatManager->playerTurn;
			}
		

			if (app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
			{
				m_players[selected_player].HP = app->combatManager->EnemyAttack(e_DMG, m_players[selected_player].HP, m_players[selected_player].DEF);
				app->combatManager->playerTurn = !app->combatManager->playerTurn;
			}


			if (app->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
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
				m_players[selected_player].HP = app->combatManager->EnemyAttack(e_DMG, m_players[selected_player].HP, m_players[selected_player].DEF);
				LOG("Atack");
				app->audio->PlayFx(fx_sword_hit);
				//Blit red color in screen
				app->render->DrawRectangle(rect, 255, 0, 0, 150);
				enemy_last_action = 0;
			}
			break;
		case 2:
			if (e_HP > 0)
			{
				app->combatManager->EnemyBlockAttack();
				LOG("Defense");
				//Blit green color in screen
				app->render->DrawRectangle(rect, 0, 255, 0, 150);
				enemy_last_action = 1;
			}
			break;
		default:
			break;
		}
		//LOG("-------------YOUR TURN-------------");
		
		app->combatManager->playerTurn = !app->combatManager->playerTurn;
		turn++;
		
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

	app->render->DrawTexture(background, 0, 0);
	
	//LOG("Player HP: %d", p_HP);
	//LOG("Enemy HP: %d", e_HP);

	// Enemy HP
	double e_percentage_life = (e_HP * 100.0) / e_max_HP;
	if (e_percentage_life < 50 && e_percentage_life >= 20)	//Yellow color
	{
		SDL_Rect rect_e = { 0, 20, 3 * e_percentage_life, 20 };
		app->render->DrawTexture(healthBar, 800, 30, &rect_e);
	}
	if (e_percentage_life < 20) //Red color
	{
		SDL_Rect rect_p = { 0, 40, 3 * e_percentage_life, 20 };
		app->render->DrawTexture(healthBar, 800, 30, &rect_p);
	}
	if (e_percentage_life >= 50) //Green color
	{
		SDL_Rect rect_p = { 0, 0, 3 * e_percentage_life, 20 };
		app->render->DrawTexture(healthBar, 800, 30, &rect_p);
	}
	app->render->DrawText("Enemy HP:", 800, 10, 100, 20, { 255, 255, 255, 255 });
	std::string e_HP_string = std::to_string(e_HP);
	app->render->DrawText(e_HP_string, 800 + 125, 10, 15, 20, { 255, 255, 255, 255 });

	//Enemy sprite

	//SDL_Rect enemy_sprite_rect = { 888, 225, 100, 115 };
	//app->render->DrawRectangle(enemy_sprite_rect, 225, 30, 30, 255);

	currentAnimationEnemy->Update();

	SDL_Rect enemyRect = currentAnimationEnemy->GetCurrentFrame();

	app->render->DrawTexture(enemyInCombat, 880, 226, &enemyRect);

	// Player 1 HP
	double p_percentage_life = (m_players[0].HP * 100.0) / m_players[0].max_HP;
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
	std::string p_HP_string = std::to_string(m_players[0].HP);
	app->render->DrawText(p_HP_string, 80 + 125, 10, 15, 20, { 255, 255, 255, 255 });

	

	// Player 2 HP
	double p2_percentage_life = (m_players[1].HP * 100.0) / m_players[1].max_HP;
	if (p2_percentage_life < 50 && p2_percentage_life >= 20)	//Yellow color
	{
		SDL_Rect rect_p2 = { 0, 20, 3 * p2_percentage_life, 20 };
		app->render->DrawTexture(healthBar, 80, 85, &rect_p2);
	}
	if (p2_percentage_life < 20) //Red color
	{
		SDL_Rect rect_p2 = { 0, 40, 3 * p2_percentage_life, 20 };
		app->render->DrawTexture(healthBar, 80, 85, &rect_p2);
	}
	if (p2_percentage_life >= 50) //Green color
	{
		SDL_Rect rect_p2 = { 0, 0, 3 * p2_percentage_life, 20 };
		app->render->DrawTexture(healthBar, 80, 85, &rect_p2);
	}
	app->render->DrawText("Player 2 HP:", 80, 70, 100, 20, { 255, 255, 255, 255 });
	std::string p2_HP_string = std::to_string(m_players[1].HP);
	app->render->DrawText(p2_HP_string, 80 + 125, 70, 15, 20, { 255, 255, 255, 255 });

	//Player 3 y 4 HP (Provisional)
	//SDL_Rect rect_p2 = { 0, 0, 300, 20 }; //p2
	//app->render->DrawTexture(healthBar, 80, 85, &rect_p2);

	SDL_Rect rect_p3 = { 0, 0, 300, 20 };	//p3
	app->render->DrawTexture(healthBar, 80, 140, &rect_p3);

	SDL_Rect rect_p4 = { 0, 0, 300, 20 };	//p4
	app->render->DrawTexture(healthBar, 80, 195, &rect_p4);


	//Player sprite
	
	//SDL_Rect player_sprite_rect = { 200, 420, 140, 160 };
	//app->render->DrawRectangle(player_sprite_rect, 180, 125, 230, 255);

	currentAnimation->Update();

	SDL_Rect playerRect = currentAnimation->GetCurrentFrame();

	if (selected_player == 0) {

		app->sceneGameplay->player->textureChange = false;
		app->render->DrawTexture(playerInCombat, 185, 405, &playerRect);

	}

	if (selected_player == 1) {

		app->sceneGameplay->player->textureChange = true;
		app->render->DrawTexture(playerInCombat2, 185, 405, &playerRect);

	}

	if (app->sceneGameplay->player->godMode)
	{
		// Combat UI - Controls (Debug)
		app->render->DrawText("1 - Standar Attack", 500, 100, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("2 - Quick Time Event Attack", 500, 115, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("3 - Defend (Block)", 500, 130, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("4 - Use Item", 500, 145, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("5 - Run away", 500, 160, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("6 - Switch Member", 500, 175, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("7 - Enemy Attack", 500, 190, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("8 - Enemy Defense", 500, 205, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("TAB - Skip Turn", 500, 230, 100, 20, { 255, 255, 255, 255 });

		//LOG - Provisional
		app->render->DrawText("Enemy Last Action: ", 500, 50, 100, 20, { 255, 255, 255, 255 });	//Last enemy action

		if (enemy_last_action == 0)
		{
			app->render->DrawText("Attack", 600, 50, 75, 20, { 255, 255, 255, 255 });
		}
		else if (enemy_last_action == 1)
		{
			app->render->DrawText("Defense", 600, 50, 75, 20, { 255, 255, 255, 255 });
		}
		else if (enemy_last_action == NULL)
		{

		}

		std::string turn_s = std::to_string(turn);								//Turn number LOG
		app->render->DrawText(turn_s, 600, 30, 15, 20, { 255, 255, 255, 255 });
		app->render->DrawText("Actual Turn: ", 500, 30, 100, 20, {255, 255, 255, 255});

	}

	
	

	

	//Combat UI - Visual
	app->render->DrawTexture(classID, 20, 20);
	app->render->DrawTexture(lifeFrame, 80, 30);	//Barra Player 1
	app->render->DrawTexture(lifeFrame, 80, 85);	//Barra Player 2
	app->render->DrawTexture(lifeFrame, 80, 140);	//Barra Player 3
	app->render->DrawTexture(lifeFrame, 80, 195);	//Barra Player 4
	app->render->DrawTexture(lifeFrame, 800, 30);	//Barra Enemy (Provisional)

	//Player selector
	switch (selected_player)
	{
	case 0:
		app->render->DrawTexture(playerSelection, 5, 29);
		break;
	case 1:
		app->render->DrawTexture(playerSelection, 5, 84);
		break;
	case 2:
		app->render->DrawTexture(playerSelection, 5, 139);
		break;
	case 3:
		app->render->DrawTexture(playerSelection, 5, 194);
		break;
	}
	

	//Atcion selector

	app->render->DrawTexture(selectionArrow, 191, 316);
	SDL_Rect actionSelector_rect = { action_selected * 70, 0, 70, 70};
	app->render->DrawTexture(actionButtons, 235, 305, &actionSelector_rect);

	if (e_HP == 0) {

		e_HP = e_max_HP;
		app->fadeToBlack->Fade(this, (Module*)app->sceneGameplay);

	}

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