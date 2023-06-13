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
#include "Timer.h"
#include "Weapon.h"

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

	for (int i = 0; i < 4; i++) {

		playerAnimation.PushBack({ 177 * (0 + i), 177 * 0, 177, 177 });

	}
	playerAnimation.loop = true;
	playerAnimation.speed = 0.06f;

	for (int i = 3; i >= 0; i--) {

		enemyAnimation32x32.PushBack({ 115 * i, 115 * 0, 115, 115 });

	}
	enemyAnimation32x32.loop = true;
	enemyAnimation32x32.speed = 0.06f;

	for (int i = 3; i >= 0; i--) {

		enemyAnimation64x32.PushBack({ 230 * i, 115 * 0, 230, 115 });

	}
	enemyAnimation64x32.loop = true;
	enemyAnimation64x32.speed = 0.06f;

	for (int i = 3; i >= 0; i--) {

		enemyAnimation32x64.PushBack({ 115 * i, 230 * 0, 115, 230 });

	}
	enemyAnimation32x64.loop = true;
	enemyAnimation32x64.speed = 0.06f;

	for (int i = 3; i >= 0; i--) {

		enemyAnimation64x64.PushBack({ 230 * i, 230 * 0, 230, 230 });

	}
	enemyAnimation64x64.loop = true;
	enemyAnimation64x64.speed = 0.06f;

	//Cambiar para después de la vertical slice
	selected_player = 0;
	turn = 0;

	//TODO
	m_players = new Party_Member[4] { {app->sceneGameplay->player->playerStats[0].hp * 10, app->sceneGameplay->player->playerStats[0].hp * 10, app->sceneGameplay->player->playerStats[0].def * 10, app->sceneGameplay->player->playerStats[0].def * 10, app->sceneGameplay->player->playerStats[0].atk * 10, app->sceneGameplay->player->playerStats[0].atk * 10, &rusticStoneAxe},
										{app->sceneGameplay->player->playerStats[1].hp * 10, app->sceneGameplay->player->playerStats[1].hp * 10, app->sceneGameplay->player->playerStats[1].def * 10, app->sceneGameplay->player->playerStats[1].def * 10, app->sceneGameplay->player->playerStats[1].atk * 10, app->sceneGameplay->player->playerStats[1].atk * 10, &fallenBlade },
										{app->sceneGameplay->player->playerStats[2].hp * 10, app->sceneGameplay->player->playerStats[2].hp * 10, app->sceneGameplay->player->playerStats[2].def * 10, app->sceneGameplay->player->playerStats[2].def * 10, app->sceneGameplay->player->playerStats[2].atk * 10, app->sceneGameplay->player->playerStats[2].atk * 10, &chainsword },
										{app->sceneGameplay->player->playerStats[3].hp * 10, app->sceneGameplay->player->playerStats[3].hp * 10, app->sceneGameplay->player->playerStats[3].def * 10, app->sceneGameplay->player->playerStats[3].def * 10, app->sceneGameplay->player->playerStats[3].atk * 10, app->sceneGameplay->player->playerStats[3].atk * 10, &graftedClaws } };

	enableMusic = true;

	//Load textures
	classID = app->tex->Load("Assets/UI/ClassID.png");
	lifeFrame = app->tex->Load("Assets/UI/Battle/LifeFrame.png");
	actionButtons = app->tex->Load("Assets/UI/ActionButtons.png");
	healthBar = app->tex->Load("Assets/UI/Battle/HealthBar.png");
	LArrow = app->tex->Load("Assets/UI/Battle/LArrow.png");
	RArrow = app->tex->Load("Assets/UI/Battle/RArrow.png");
	playerSelection = app->tex->Load("Assets/UI/PlayerSelector.png");
	q_sprite = app->tex->Load("Assets/Textures/q.png");
	dialogue = app->tex->Load("Assets/Textures/dialogue-UI.png");
	Turn = app->tex->Load("Assets/UI/Battle/TURN.png");
	MedievalTurn = app->tex->Load("Assets/UI/Battle/MedievalTurn.png");
	PrehistoricalTurn = app->tex->Load("Assets/UI/Battle/PrehistoricalTurn.png");
	CyberpunkTurn = app->tex->Load("Assets/UI/Battle/CyberpunkTurn.png");
	ApocalypseTurn = app->tex->Load("Assets/UI/Battle/ApocalypseTurn.png");
	EnemyTurn = app->tex->Load("Assets/UI/Battle/EnemyTurn.png");

	//Load audios
	fx_sword_hit = app->audio->LoadFx("Assets/Audio/FX/SceneBattle/SwordFX.wav");
	selectFX = app->audio->LoadFx("Assets/Audio/FX/SceneBattle/Select.wav");
	healFX = app->audio->LoadFx("Assets/Audio/FX/SceneBattle/Heal.wav");
	skillFX = app->audio->LoadFx("Assets/Audio/FX/SceneBattle/Fire.wav");
	clawsFX = app->audio->LoadFx("Assets/Audio/FX/SceneBattle/Claws.wav");
	runFX = app->audio->LoadFx("Assets/Audio/FX/SceneBattle/Run.wav");
	receiveHitFX = app->audio->LoadFx("Assets/Audio/FX/SceneBattle/Hit.wav");
	battleStartFX = app->audio->LoadFx("Assets/Audio/FX/SceneBattle/BattleStart.wav");
	failedToRunFX = app->audio->LoadFx("Assets/Audio/FX/SceneBattle/FailedToRun.wav");
	enemyFailFX = app->audio->LoadFx("Assets/Audio/FX/SceneBattle/EnemyFail.wav");

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

	medievalInCombat = app->tex->Load("Assets/Textures/Medieval_InCombat.png");
	prehistoricInCombat = app->tex->Load("Assets/Textures/Prehistoric_InCombat.png");
	cyberpunkInCombat = app->tex->Load("Assets/Textures/Cyberpunk_InCombat.png");
	apocalypseInCombat = app->tex->Load("Assets/Textures/Apocalypse_InCombat.png");

	// Enemy texture

	currentAnimationEnemy = &enemyAnimation32x32;

	background = app->tex->Load("Assets/Textures/BattleBackground.png");

	arrow1 = { 0, 0, 25, 46 };
	arrow2 = { 0, 46, 25, 46 };


	return true;
}

// Called each loop iteration
bool SceneBattle::PreUpdate()
{
	OPTICK_EVENT();

	app->entityManager->Disable();

	if (enableMusic) {

		app->audio->PlayMusic("Assets/Audio/Music/BattleTheme.ogg", 0);

		app->audio->PlayFx(battleStartFX);

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

	if (widthEnemyCombat == 32 && heightEnemyCombat == 32) {

		currentAnimationEnemy = &enemyAnimation32x32;

	}
	else if (widthEnemyCombat == 32 && heightEnemyCombat == 64) {

		currentAnimationEnemy = &enemyAnimation32x64;

	}
	else if (widthEnemyCombat == 64 && heightEnemyCombat == 32) {

		currentAnimationEnemy = &enemyAnimation64x32;

	}
	else if (widthEnemyCombat == 64 && heightEnemyCombat == 64) {

		currentAnimationEnemy = &enemyAnimation64x64;

	}

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
		if (!qte)
		{

			//Standar actions
			if (app->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
				app->sceneGameplay->player->godMode = !app->sceneGameplay->player->godMode;

			if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
			{
				

				if (action_selected != 0)
				{
					action_selected--;

				}
				else if (action_selected == 0)
				{
					action_selected = 6;
				}

				app->audio->PlayFx(selectFX);

			}

			if (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			{

				

				if (action_selected != 6)
				{
					action_selected++;
				}
				else if (action_selected == 6)
				{
					action_selected = 0;
				}

				app->audio->PlayFx(selectFX);

			}

			if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
			{
				combat_timmer.Start();
				switch (action_selected)
				{
				case 0: //Standar attack
					if (minion) 
					{
						m_HP = app->combatManager->NormalAttack(m_players[selected_player].DMG, m_HP, m_DEF);
					}
					else
					{
						e_HP = app->combatManager->NormalAttack(m_players[selected_player].DMG, e_HP, e_DEF);
					}
					app->audio->PlayFx(fx_sword_hit);
					app->combatManager->playerTurn = !app->combatManager->playerTurn;
					app->audio->PlayFx(fx_sword_hit);
					break;
				case 1:	//Quick time event attack (TODO)
					qte_timer.Start();
					qte = true;
					app->audio->PlayFx(clawsFX);
					break;
				case 2: //Swap Weapons
					
					app->combatManager->ChangeWeapon(selected_player, m_players[selected_player].equippedWeapon);
					app->audio->PlayFx(app->sceneGameplay->player->changeFX);
					app->combatManager->playerTurn = !app->combatManager->playerTurn;
					break;

				case 3: //Heal

					m_players[selected_player].HP = app->combatManager->UseItem(m_players[selected_player].HP);
					app->combatManager->playerTurn = !app->combatManager->playerTurn;
					app->audio->PlayFx(healFX);
					break;

				case 4: //Habilidades (TODO)

					app->combatManager->SkillAttack(selected_player, m_players[selected_player].DMG, m_players[selected_player].DEF);
					app->audio->PlayFx(skillFX);
					app->combatManager->playerTurn = !app->combatManager->playerTurn;
					break;

				case 5: //Run away

					if (app->combatManager->Run())
					{
						//Transition to Gameplay Screen
						app->audio->PlayFx(runFX);
						app->audio->PlayMusic("Assets/Audio/Music/Level1_Music.ogg", 0);
						enableMusic = true;
						app->fadeToBlack->Fade(this, (Module*)app->sceneGameplay);
						app->combatManager->playerTurn = !app->combatManager->playerTurn;

					}
					else
					{
						LOG("You failed to run away");
						app->audio->PlayFx(failedToRunFX);
						app->combatManager->playerTurn = !app->combatManager->playerTurn;
					}
					break;

				case 6:

					selected_player = app->combatManager->ChangeParty(selected_player);
					app->audio->PlayFx(app->sceneGameplay->player->changeFX);
					app->combatManager->playerTurn = !app->combatManager->playerTurn;

					break;
				}
				
			}

			if (m_players[0].HP == 0 && m_players[1].HP == 0 && m_players[2].HP == 0 && m_players[3].HP == 0)
			{
				app->fadeToBlack->Fade((Module*)app->sceneBattle, (Module*)app->sceneEnding);
				m_players[0].HP = m_players[0].max_HP;
				m_players[1].HP = m_players[1].max_HP;
				m_players[2].HP = m_players[2].max_HP;
				m_players[3].HP = m_players[3].max_HP;
			}

			//Reset de la vida del minion
			if (m_HP == 0)
			{
				minion = false;
				m_HP = m_max_HP;
			}

			//Debug controls
			if (app->sceneGameplay->player->godMode)
			{
				if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
				{
					e_HP = app->combatManager->NormalAttack(m_players[selected_player].DMG, e_HP, e_DEF);
					app->combatManager->playerTurn = !app->combatManager->playerTurn;

				}


				if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
				{
					//e_HP = app->combatManager->StandarAttack(m_players[selected_player].DMG, e_HP, e_DEF);
					//app->combatManager->playerTurn = !app->combatManager->playerTurn;
					///*qte = true;
					//startTime = SDL_GetTicks();*/

					qte_timer.Start();
					qte = true;

				}


				if (app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
				{
					app->combatManager->SkillAttack(selected_player, m_players[selected_player].DMG, m_players[selected_player].DEF);
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

				if (app->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN)		//Heal enemy HP
					e_HP = e_max_HP;

				if (app->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)		//Reset enemy HP
					e_HP = 1;

				if (app->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT && app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)		//Reset player HP
					m_players[selected_player].HP = 1;

				if (app->input->GetKey(SDL_SCANCODE_TAB) == KEY_DOWN)
					app->combatManager->playerTurn = !app->combatManager->playerTurn;

				if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
					minion = !minion;
			}
		}

		// Quick Time Event - Timer
		if (qte)
		{
			LOG("Quick Time Event Started");

			if (qte_timer.ReadMSec() > 2000)
			{
				//Weapon Hit - Si fallas el QTE vas a hacer poco daño
				if (minion)
				{
					m_HP = app->combatManager->WeaponAttack(m_players[selected_player].DMG * 0.75, m_HP, m_DEF, false, num_hits);
				}
				else
				{
					e_HP = app->combatManager->WeaponAttack(m_players[selected_player].DMG * 0.75, e_HP, e_DEF, false, num_hits);
				}
				
				

				qte = false;
				num_hits = 0; // Reiniciar el contador de hits
				app->combatManager->playerTurn = !app->combatManager->playerTurn;
			}


			if ((app->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN))
			{
				delay = qte_timer.ReadMSec();
				
				LOG("QTE-Inicio (MS): %f", qte_timer.ReadMSec());
				//Reset qte_timer
				qte_timer.Start();

				if (delay > 500 && delay < 1500)
				{
					num_hits++; // Incrementar el contador de pulsaciones

					// Si el jugador ha presionado la tecla Q suficientes veces, llama a TimeEventAttack con un valor de MAX_HITS y reinicia el contador
					if (num_hits == MAX_HITS)
					{
						//Weapon Hit 
						if (minion)
						{
							m_HP = app->combatManager->WeaponAttack(m_players[selected_player].DMG, m_HP, m_DEF, true, MAX_HITS);
						}
						else
						{
							e_HP = app->combatManager->WeaponAttack(m_players[selected_player].DMG, e_HP, e_DEF, true, MAX_HITS);
						}
						
						
						
						qte = false;
						num_hits = 0; // Reiniciar el contador de hits
						app->combatManager->playerTurn = !app->combatManager->playerTurn;

					}
				}
				else       //Bad timing
				{
					//Weapon Hit 
					if (minion)
					{
						m_HP = app->combatManager->WeaponAttack(m_players[selected_player].DMG, m_HP, m_DEF, true, num_hits);
					}
					else
					{
						e_HP = app->combatManager->WeaponAttack(m_players[selected_player].DMG, e_HP, e_DEF, true, num_hits);
					}
						
					qte = false;
					num_hits = 0; // Reiniciar el contador de hits
					app->combatManager->playerTurn = !app->combatManager->playerTurn;
				}
			}

		}
	}
	else
	{	
		if (boss == 0)	//Comprobar si es un enemigo o un boss - TODO
		{
			//Timer enemigo
			if (!timer_started)
			{
				timer.Start();
				timer_started = true;
			}
			if (timer.ReadMSec() >= 1000)
			{

				//LOG("-------------ENEMY TURN-------------");
				int random_num = (rand() % 2) + 1;
				//LOG("Numero aleatorio %d", random_num);
				switch (random_num)
				{
				case 1:
					if (e_HP > 0)
					{
						if (e_confusion_turns == 0 && m_players[selected_player].counter_turns == 0)
							m_players[selected_player].HP = app->combatManager->EnemyAttack(e_DMG, m_players[selected_player].HP, m_players[selected_player].DEF);

						//Si el enemigo tiene confusión su turno será como si se atacara a si mismo
						if (e_confusion_turns > 0)
							e_HP = app->combatManager->NormalAttack(e_DMG, e_HP, e_DEF);

						//Si el player tiene counter turns el enemigo sufre daño al atacar al player
						if (m_players[selected_player].counter_turns > 0)
						{
							m_players[selected_player].HP = app->combatManager->EnemyAttack(e_DMG, m_players[selected_player].HP, m_players[selected_player].DEF);
							e_HP = app->combatManager->NormalAttack(e_DMG, e_HP, e_DEF);
						}

						LOG("Atack");
						app->audio->PlayFx(receiveHitFX);
						//app->audio->PlayFx(fx_sword_hit); //Se buguea un montón porque se sobreponen los sonidos, hay que  añadirle un timer o algo para evitarlo y que sea algo mas lento el combate
						//Blit red color in screen
						//app->render->DrawRectangle(rect, 255, 0, 0, 150);
						enemy_last_action = 0;
					}
					break;
				case 2:
					if (e_HP > 0)
					{
						app->combatManager->EnemyBlockAttack();
						LOG("Defense");
						//Blit green color in screen
						//app->render->DrawRectangle(rect, 0, 255, 0, 150);
						enemy_last_action = 1;
						app->audio->PlayFx(enemyFailFX);
					}
					break;
				default:
					break;
				}
				//LOG("-------------YOUR TURN-------------");

				combat_timmer.Start();

				//Confusion enemy
				if (e_confusion_turns > 0)
					e_confusion_turns--;

				//Buff stats enemy
				if (e_buffed_turns > 0)
					e_buffed_turns--;

				if (e_buffed_turns == 0)
				{
					e_DEF = e_base_DEF;
					e_DMG = e_base_DMG;
				}

				//Skill Mage - Middle ages steroids
				for (int i = 0; i < 3; i++)
				{
					if (m_players[i].buf_turns == 0)
					{
						m_players[i].DEF = m_players[i].base_DEF;
						m_players[i].DMG = m_players[i].base_DMG;
					}
					if (m_players[i].buf_turns > 0)
						m_players[i].buf_turns--;

				}

				//Skill Tank - I'm the one who bonks!
				for (int i = 0; i < 3; i++)
				{
					if (m_players[i].counter_turns > 0)
						m_players[i].counter_turns--;
				}


				app->combatManager->playerTurn = !app->combatManager->playerTurn;
				turn++;
				timer_started = false;
			}
		}
		else
		{
			//Habria que meter un switch o algo que permitiera controlar si te estás enfrentando con el primero, segundo, tercero o Final Boss para decicir las
			//habilidades y los % de los diferentes ataques y habilidades

			if (boss == 1)		//Primer boss - Summon minions every two turns
			{
				

			}
			else if (boss == 2)	//Segundo boss - Se buffea en un %
			{
				

			}
			else if (boss == 3)	//Tercer boss - ???
			{
				

			}
			else if (boss == 4)	//Boss final - Ataca a todos los players + todo lo anterior
			{
				

			}

		}
		
	}

	//---

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) {

		enableMusic = true;
		app->fadeToBlack->Fade(this, (Module*)app->sceneGameplay);
	}

	if (combat_timmer.ReadMSec() < 2000)
	{
		show_battle_info = true;
	}
	else
	{
		show_battle_info = false;
	}

	if (m_players[selected_player].HP == 0)
	{
		if (selected_player == 3)
		{
			selected_player = 0;
		}
		else
		{
			selected_player++;
		}
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
		SDL_Rect rect_e = { 0, 18 * 1, 2.85 * e_percentage_life, 18 };
		app->render->DrawTexture(healthBar, 802, 31, &rect_e);
	}
	if (e_percentage_life < 20) //Red color
	{
		SDL_Rect rect_p = { 0, 18 * 2, 2.85 * e_percentage_life, 18 };
		app->render->DrawTexture(healthBar, 802, 31, &rect_p);
	}
	if (e_percentage_life >= 50) //Green color
	{
		SDL_Rect rect_p = { 0, 18 * 0, 2.85 * e_percentage_life, 18 };
		app->render->DrawTexture(healthBar, 802, 31, &rect_p);
	}
	app->render->DrawText("Enemy HP:", 800, 10, 100, 20, { 255, 255, 255, 255 });
	std::string e_HP_string = std::to_string(e_HP);
	app->render->DrawText(e_HP_string, 800 + 125, 10, 15, 20, { 255, 255, 255, 255 });

	//Minion sprite
	if (minion)
	{
		currentAnimationEnemy->Update();

		SDL_Rect minionRect = currentAnimationEnemy->GetCurrentFrame();

		app->render->DrawTexture(enemyInCombat, 780, 426, &minionRect);

		// Minion HP
		double m_percentage_life = (m_HP * 100.0) / m_max_HP;
		if (m_percentage_life < 50 && m_percentage_life >= 20)	//Yellow color
		{
			SDL_Rect rect_m = { 0, 18 * 1, 2.85 * m_percentage_life, 18 };
			app->render->DrawTexture(healthBar, 722, 403, &rect_m);
		}
		if (m_percentage_life < 20) //Red color
		{
			SDL_Rect rect_m = { 0, 18 * 2, 2.85 * m_percentage_life, 18 };
			app->render->DrawTexture(healthBar, 722, 403, &rect_m);
		}
		if (m_percentage_life >= 50) //Green color
		{
			SDL_Rect rect_m = { 0, 18 * 0, 2.85 * m_percentage_life, 18 };
			app->render->DrawTexture(healthBar, 722, 403, &rect_m);
		}
		app->render->DrawText("Minion HP:", 720, 380, 100, 20, { 255, 255, 255, 255 });
		std::string m_HP_string = std::to_string(m_HP);
		app->render->DrawText(m_HP_string, 720 + 125, 380, 15, 20, { 255, 255, 255, 255 });
	}

	//Enemy sprite

	//SDL_Rect enemy_sprite_rect = { 888, 225, 100, 115 };
	//app->render->DrawRectangle(enemy_sprite_rect, 225, 30, 30, 255);

	currentAnimationEnemy->Update();

	SDL_Rect enemyRect = currentAnimationEnemy->GetCurrentFrame();

	if (widthEnemyCombat == 32 && heightEnemyCombat == 32) {

		app->render->DrawTexture(enemyInCombat, 880, 226, &enemyRect);

	}
	else if (widthEnemyCombat == 32 && heightEnemyCombat == 64) {

		app->render->DrawTexture(enemyInCombat, 880, 194, &enemyRect);

	}
	else if (widthEnemyCombat == 64 && heightEnemyCombat == 32) {

		app->render->DrawTexture(enemyInCombat, 848, 226, &enemyRect);

	}
	else if (widthEnemyCombat == 64 && heightEnemyCombat == 64) {

		app->render->DrawTexture(enemyInCombat, 848, 194, &enemyRect);

	}

	// Player 1 HP
	double p_percentage_life = (m_players[0].HP * 100.0) / m_players[0].max_HP;
	if (p_percentage_life < 50 && p_percentage_life >= 20)	//Yellow color
	{
		SDL_Rect rect_p = { 0, 18 * 1, 2.85 * p_percentage_life, 18 };
		app->render->DrawTexture(healthBar, 81, 31, &rect_p);
	}
	if (p_percentage_life < 20) //Red color
	{
		SDL_Rect rect_p = { 0, 18 * 2, 2.85 * p_percentage_life, 18 };
		app->render->DrawTexture(healthBar, 81, 31, &rect_p);
	}
	if (p_percentage_life >= 50) //Green color
	{
		SDL_Rect rect_p = { 0, 18 * 0, 2.85 * p_percentage_life, 18 };
		app->render->DrawTexture(healthBar, 81, 31, &rect_p);
	}
	app->render->DrawText("Player HP:", 80, 10, 100, 20, { 255, 255, 255, 255 });
	std::string p_HP_string = std::to_string(m_players[0].HP);
	app->render->DrawText(p_HP_string, 80 + 125, 10, 15, 20, { 255, 255, 255, 255 });

	

	// Player 2 HP
	double p2_percentage_life = (m_players[1].HP * 100.0) / m_players[1].max_HP;
	if (p2_percentage_life < 50 && p2_percentage_life >= 20)	//Yellow color
	{
		SDL_Rect rect_p2 = { 0, 18 * 1, 2.85 * p2_percentage_life, 18 };
		app->render->DrawTexture(healthBar, 81, 86, &rect_p2);
	}
	if (p2_percentage_life < 20) //Red color
	{
		SDL_Rect rect_p2 = { 0, 18 * 2, 2.85 * p2_percentage_life, 18 };
		app->render->DrawTexture(healthBar, 81, 86, &rect_p2);
	}
	if (p2_percentage_life >= 50) //Green color
	{
		SDL_Rect rect_p2 = { 0, 18 * 0, 2.85 * p2_percentage_life, 18 };
		app->render->DrawTexture(healthBar, 81, 86, &rect_p2);
	}
	app->render->DrawText("Player 2 HP:", 80, 70, 100, 20, { 255, 255, 255, 255 });
	std::string p2_HP_string = std::to_string(m_players[1].HP);
	app->render->DrawText(p2_HP_string, 80 + 125, 70, 15, 20, { 255, 255, 255, 255 });

	// Player 3 HP
	double p3_percentage_life = (m_players[2].HP * 100.0) / m_players[2].max_HP;
	if (p3_percentage_life < 50 && p3_percentage_life >= 20)	//Yellow color
	{
		SDL_Rect rect_p3 = { 0, 18 * 1, 2.85 * p3_percentage_life, 18 };
		app->render->DrawTexture(healthBar, 81, 141, &rect_p3);
	}
	if (p3_percentage_life < 20) //Red color
	{
		SDL_Rect rect_p3 = { 0, 18 * 2, 2.85 * p3_percentage_life, 18 };
		app->render->DrawTexture(healthBar, 81, 141, &rect_p3);
	}
	if (p3_percentage_life >= 50) //Green color
	{
		SDL_Rect rect_p3 = { 0, 18 * 0, 2.85 * p3_percentage_life, 18 };
		app->render->DrawTexture(healthBar, 81, 141, &rect_p3);
	}
	app->render->DrawText("Player 3 HP:", 80, 120, 100, 20, { 255, 255, 255, 255 });
	std::string p3_HP_string = std::to_string(m_players[2].HP);
	app->render->DrawText(p3_HP_string, 80 + 125, 120, 15, 20, { 255, 255, 255, 255 });

	// Player 4 HP
	double p4_percentage_life = (m_players[3].HP * 100.0) / m_players[3].max_HP;
	if (p4_percentage_life < 50 && p4_percentage_life >= 20)	//Yellow color
	{
		SDL_Rect rect_p4 = { 0, 18 * 1, 2.85 * p4_percentage_life, 18 };
		app->render->DrawTexture(healthBar, 81, 197, &rect_p4);
	}
	if (p4_percentage_life < 20) //Red color
	{
		SDL_Rect rect_p4 = { 0, 18 * 2, 2.85 * p4_percentage_life, 18 };
		app->render->DrawTexture(healthBar, 81, 197, &rect_p4);
	}
	if (p4_percentage_life >= 50) //Green color
	{
		SDL_Rect rect_p4 = { 0, 18 * 0, 2.85 * p4_percentage_life, 18 };
		app->render->DrawTexture(healthBar, 81, 197, &rect_p4);
	}
	app->render->DrawText("Player 4 HP:", 80, 175, 100, 20, { 255, 255, 255, 255 });
	std::string p4_HP_string = std::to_string(m_players[3].HP);
	app->render->DrawText(p4_HP_string, 80 + 125, 175, 15, 20, { 255, 255, 255, 255 });

	//SDL_Rect rect_p3 = { 0, 0, 300, 20 };	//p3
	//app->render->DrawTexture(healthBar, 80, 140, &rect_p3);

	//SDL_Rect rect_p4 = { 0, 0, 300, 20 };	//p4
	//app->render->DrawTexture(healthBar, 80, 195, &rect_p4);


	//Player sprite
	
	//SDL_Rect player_sprite_rect = { 200, 420, 140, 160 };
	//app->render->DrawRectangle(player_sprite_rect, 180, 125, 230, 255);

	currentAnimation->Update();

	SDL_Rect playerRect = currentAnimation->GetCurrentFrame();

	if (selected_player == 0) {

		app->sceneGameplay->player->playerChange = 0;
		app->render->DrawTexture(medievalInCombat, 185, 405, &playerRect);

	}

	if (selected_player == 1) {

		app->sceneGameplay->player->playerChange = 1;
		app->render->DrawTexture(prehistoricInCombat, 185, 405, &playerRect);

	}

	if (selected_player == 2) {

		app->sceneGameplay->player->playerChange = 2;
		app->render->DrawTexture(cyberpunkInCombat, 185, 405, &playerRect);

	}

	if (selected_player == 3) {

		app->sceneGameplay->player->playerChange = 3;
		app->render->DrawTexture(apocalypseInCombat, 185, 405, &playerRect);

	}

	if (app->sceneGameplay->player->godMode)
	{
		// Combat UI - Controls (Debug) (Tamaño fuente: 8,3 x Nº de caracteres del string)
		app->render->DrawText("1 - Normal Attack", 500, 100, 150, 20, { 255, 255, 255, 255 });
		app->render->DrawText("2 - Weapon Attack", 500, 115, 150, 20, { 255, 255, 255, 255 });
		app->render->DrawText("3 - Skill Attack", 500, 130, 150, 20, { 255, 255, 255, 255 });
		app->render->DrawText("4 - Use Item", 500, 145, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("5 - Run away", 500, 160, 100, 20, { 255, 255, 255, 255 });
		app->render->DrawText("6 - Switch Member", 500, 175, 142, 20, { 255, 255, 255, 255 });
		app->render->DrawText("7 - Enemy Attack", 500, 190, 133, 20, { 255, 255, 255, 255 });
		app->render->DrawText("8 - Enemy Defense", 500, 205, 142, 20, { 255, 255, 255, 255 });
		app->render->DrawText("H - Enemy Full Recover", 500, 220, 183, 20, { 255, 255, 255, 255 });
		app->render->DrawText("TAB - Skip Turn", 500, 235, 125, 20, { 255, 255, 255, 255 });

		//LOG - Provisional
		app->render->DrawText("Enemy Last Action: ", 500, 50, 158, 20, { 255, 255, 255, 255 });	//Last enemy action

		if (enemy_last_action == 0)
		{
			app->render->DrawText("Attack", 660, 50, 50, 20, { 255, 255, 255, 255 });
		}
		else if (enemy_last_action == 1)
		{
			app->render->DrawText("Defense", 660, 50, 58, 20, { 255, 255, 255, 255 });
		}
		else if (enemy_last_action == NULL)
		{

		}

		std::string turn_s = std::to_string(turn);								//Turn number LOG
		app->render->DrawText(turn_s, 600, 30, 15, 20, { 255, 255, 255, 255 });
		app->render->DrawText("Actual Turn: ", 500, 30, 100, 20, {255, 255, 255, 255});


		app->render->DrawText("QTE: ", 500, 10, 50, 20, { 255, 255, 255, 255 });	//Quick Time Event
		if (qte)
		{
			app->render->DrawText("ON", 550, 10, 10, 20, { 255, 255, 255, 255 });	
		}
		else
		{
			app->render->DrawText("OFF", 550, 10, 10, 20, { 255, 255, 255, 255 });	
		}

		//Muestra el numero de veces que se golpea al enemigo (dentro de cada QTE)
		std::string hits = std::to_string(num_hits);
		app->render->DrawText(hits, 575, 10, 10, 20, { 255, 255, 255, 255 });	

		//Debug Draw (QTE)
		app->render->DrawText("Timer: ", 110, 400, 40, 20, {255, 255, 255, 255});
		std::string time = std::to_string(qte_timer.ReadMSec());
		app->render->DrawText(time, 150, 400, 100, 20, { 255, 255, 255, 255 });

		//Muestra la cantidad de turnos que le quedan con confusión al enemigo
		std::string confusion = std::to_string(e_confusion_turns);
		app->render->DrawText(confusion, 1000+100, 10, 10, 20, { 255, 255, 255, 255 });
		app->render->DrawText("Confusion turns: ", 900+100, 10, 100, 20, { 255, 255, 255, 255 });


		if (minion)
		{
			app->render->DrawText("Minion: ON", 720, 350, 100, 20, { 255, 255, 255, 255 });
		}
		else
		{
			app->render->DrawText("Minion: OFF", 720, 350, 100, 20, { 255, 255, 255, 255 });
		}
	}


	//Combat UI - Visual
	app->render->DrawTexture(classID, 20, 20);
	app->render->DrawTexture(lifeFrame, 78, 28);	//Barra Player 1
	app->render->DrawTexture(lifeFrame, 78, 83);	//Barra Player 2
	app->render->DrawTexture(lifeFrame, 78, 138);	//Barra Player 3
	app->render->DrawTexture(lifeFrame, 78, 194);	//Barra Player 4
	app->render->DrawTexture(lifeFrame, 799, 28);	//Barra Enemy (Provisional)
	if (minion)
		app->render->DrawTexture(lifeFrame, 720, 400);	//Barra Minion (Provisional)

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

	SDL_Rect actionSelector_rect = { action_selected * 70, 0, 70, 70};
	app->render->DrawTexture(actionButtons, 235, 305, &actionSelector_rect);

	if (e_HP == 0) {

		app->combatManager->playerTurn = true;
		e_HP = e_max_HP;
		for (int i = 0; i < 4; i++)
		{
			app->sceneGameplay->player->AddXP(100, i);
		}
		turn = 0;
		app->fadeToBlack->Fade(this, (Module*)app->sceneGameplay);

	}

	//QTE - Mostrar algo cuando es buen momento para volver a pulsar la Q
	if (qte_timer.ReadMSec() > 500 && qte_timer.ReadMSec() < 1500 && qte)
	{
		app->render->DrawTexture(q_sprite, 350, 400);
	}

	if (show_battle_info)
	{
		app->render->DrawTexture(dialogue, 650, 525);

		if (app->combatManager->playerTurn)	//Turno enemigo
		{
			if (enemy_last_action == 0)
			{
				app->render->DrawText("Enemy Attacked you!", 700, 568, 310, 30, { 90, 35, 24, 255 });
			}
			else if (enemy_last_action == 1)
			{
				app->render->DrawText("Enemy Defended himself!", 700, 568, 310, 30, { 90, 35, 24, 255 });
			}
			else if (enemy_last_action == NULL)
			{

			}
		}
		else                                    //Turno del jugaddor
		{
			switch (action_selected)
			{
			case 0:
				app->render->DrawText("You attacked the enemy with Normal Attack", 700, 568, 500, 30, { 90, 35, 24, 255 });
				break;
			case 1:
				app->render->DrawText("You attacked the enemy with your weapon", 700, 568, 500, 30, { 90, 35, 24, 255 });
				break;
			case 2:
				app->render->DrawText("You used an item - Heal", 700, 568, 375, 30, { 90, 35, 24, 255 });
				break;
			case 3:
				app->render->DrawText("You attacked the enemy with your skill", 700, 568, 500, 30, { 90, 35, 24, 255 });
				break;
			case 4:
				app->render->DrawText("You tried to run away", 700, 568, 440, 30, { 90, 35, 24, 255 });
				break;
			case 5:
				app->render->DrawText("You switched your party member", 700, 568, 456, 30, { 90, 35, 24, 255 });
				break;
			}
		}
	}


	app->render->DrawTexture(LArrow, 208, 318, &arrow1);
	app->render->DrawTexture(RArrow, 307, 318, &arrow1);

	if (app->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
	{
		app->render->DrawTexture(LArrow, 205, 318, &arrow2);
	}

	if (app->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
	{
		app->render->DrawTexture(RArrow, 304, 318, &arrow2);
	}

	app->render->DrawTexture(Turn, 597, 36);

	if (app->combatManager->playerTurn) {

		switch (selected_player) {
		case 0:

			app->render->DrawTexture(MedievalTurn, 576, 68);
			break;

		case 1:

			app->render->DrawTexture(PrehistoricalTurn, 576, 68);
			break;

		case 2:

			app->render->DrawTexture(CyberpunkTurn, 576, 68);
			break;
		case 3:

			app->render->DrawTexture(ApocalypseTurn, 576, 68);
			break;
		}
		
	}
	else {

		app->render->DrawTexture(EnemyTurn, 576, 31);
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