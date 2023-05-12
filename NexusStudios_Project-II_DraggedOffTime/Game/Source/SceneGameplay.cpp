#include "App.h"
#include "Defs.h"
#include "Log.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Physics.h"
#include "Window.h"
#include "Map.h"
#include "FadeToBlack.h"
#include "EntityManager.h"
#include "SceneTitle.h"
#include "Tweening.h"

#include "SceneGameplay.h"

#include "SDL_mixer/include/SDL_mixer.h"

SceneGameplay::SceneGameplay(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneGameplay");
}

// Destructor
SceneGameplay::~SceneGameplay()
{}

bool SceneGameplay::Awake(pugi::xml_node& config)
{
	player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
	player->parameters = config.child("player");

	for (pugi::xml_node npcNode = config.child("npc"); npcNode; npcNode = npcNode.next_sibling("npc"))
	{
		NPC* npc = (NPC*)app->entityManager->CreateEntity(EntityType::NPC);
		npc->parameters = npcNode;

		npcs.Add(npc);

	}

	for (pugi::xml_node enemyNode = config.child("enemy"); enemyNode; enemyNode = enemyNode.next_sibling("enemy"))
	{
		Enemy* enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
		enemy->parameters = enemyNode;

		enemies.Add(enemy);

	}

	for (pugi::xml_node itemNode = config.child("item"); itemNode; itemNode = itemNode.next_sibling("item"))
	{
		Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
		item->parameters = itemNode;

	}
	
	return true;
}

// Called before the first frame
bool SceneGameplay::Start()
{
	app->map->actualmap = 0;

	/*Juan = app->tex->Load("Assets/UI/Back.png");

	Juan_anim.Set();
	Juan_anim.smoothness = 4;
	Juan_anim.AddTween(50, 150, EXPONENTIAL_OUT);*/
	bool retLoad = app->map->Load();
	//app->map->Enable();

	enableMusic = true;

	// Pause

	pause.Load();

	// Stats

	featureMenu.Load();

	return true;
}

// Called each loop iteration
bool SceneGameplay::PreUpdate()
{
	OPTICK_EVENT();

	if (enableMusic) {

		app->audio->PlayMusic("Assets/Audio/Music/Level1_Music.ogg", 0);
		enableMusic = false;

	}

	return true;
}

// Called each loop iteration
bool SceneGameplay::Update(float dt)
{
	OPTICK_EVENT();

	//Player

	if (player->godMode == true)
	{
		if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
		{
			map_selector = true;
		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && actually == 0)
		{
			
			app->map->CleanUp();
			app->map->actualmap = 1;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 1;
			app->sceneGameplay->player->Teleport(650, 700);

			//Move Npcs Map_1
			npcs.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(0)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			
			npcs.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(1)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			
			npcs.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);
			npcs.At(2)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);

			//Move Enemies Map_1
			enemies.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(0)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(1)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(2)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			
			enemies.At(3)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(3)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);


		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && actually == 0)
		{
			app->map->CleanUp();
			app->map->actualmap = 2;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 2;
			app->sceneGameplay->player->Teleport(650, 700);
			
			//Move Npcs Map_2
			npcs.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(0)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(1)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(2)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			//Move Enemies Map_2
			enemies.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(0)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(1)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(2)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(3)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(3)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && actually == 1)
		{

			app->map->CleanUp();
			app->map->actualmap = 0;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 0;
			app->sceneGameplay->player->Teleport(150, 430);
			
			//Move Npcs Map_0
			npcs.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(950),PIXEL_TO_METERS(410) }, 0);
			npcs.At(0)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(950),PIXEL_TO_METERS(410) }, 0);

			npcs.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(755),PIXEL_TO_METERS(350) }, 0);
			npcs.At(1)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(755),PIXEL_TO_METERS(350) }, 0);

			npcs.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(420) }, 0);
			npcs.At(2)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(420) }, 0);
			
			//Move Npcs Map_0
			enemies.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(690),PIXEL_TO_METERS(160) }, 0);
			enemies.At(0)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(690),PIXEL_TO_METERS(160) }, 0);

			enemies.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(1050),PIXEL_TO_METERS(160) }, 0);
			enemies.At(1)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(1050),PIXEL_TO_METERS(160) }, 0);

			enemies.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(615) }, 0);
			enemies.At(2)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(615) }, 0);

			enemies.At(3)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(1120),PIXEL_TO_METERS(600) }, 0);
			enemies.At(3)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(1120),PIXEL_TO_METERS(600) }, 0);
		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && actually == 1)
		{

			app->map->CleanUp();
			app->map->actualmap = 2;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 2;
			app->sceneGameplay->player->Teleport(650, 700);
			
			//Move Npcs Map_2
			npcs.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(0)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(1)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(2)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			//Move Enemies Map_2
			enemies.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(0)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(1)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(2)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(3)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			enemies.At(3)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && actually == 2)
		{
			app->map->CleanUp();
			app->map->actualmap = 0;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 0;
			app->sceneGameplay->player->Teleport(150, 430);

			//Move Npcs Map_0
			npcs.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(950),PIXEL_TO_METERS(410) }, 0);
			npcs.At(0)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(950),PIXEL_TO_METERS(410) }, 0);

			npcs.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(755),PIXEL_TO_METERS(350) }, 0);
			npcs.At(1)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(755),PIXEL_TO_METERS(350) }, 0);

			npcs.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(420) }, 0);
			npcs.At(2)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(420) }, 0);
			
			//Move Enemies Map_0
			enemies.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(690),PIXEL_TO_METERS(160) }, 0);
			enemies.At(0)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(690),PIXEL_TO_METERS(160) }, 0);

			enemies.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(1050),PIXEL_TO_METERS(160) }, 0);
			enemies.At(1)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(1050),PIXEL_TO_METERS(160) }, 0);

			enemies.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(615) }, 0);
			enemies.At(2)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(75),PIXEL_TO_METERS(615) }, 0);

			enemies.At(3)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(1120),PIXEL_TO_METERS(600) }, 0);
			enemies.At(3)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(1120),PIXEL_TO_METERS(600) }, 0);
		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && actually == 2)
		{
			app->map->CleanUp();
			app->map->actualmap = 1;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 1;
			app->sceneGameplay->player->Teleport(650, 700);
			
			//Move Npcs Map_1
			npcs.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(0)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.At(1)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);
			npcs.At(2)->data->npcSensor->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);

			//Move Enemies Map_1
			enemies.At(0)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(0)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(1)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(1)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(2)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(2)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.At(3)->data->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.At(3)->data->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		}
	}

	if (!app->entityManager->IsEnabled()) {

		app->entityManager->Enable();

	}

	if (app->sceneGameplay->player->godMode) app->physics->debug = true;
	else app->physics->debug = false;

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) {

		enableMusic = true;
		app->fadeToBlack->Fade(this, (Module*)app->sceneBattle);

	}

	app->map->Draw();

	// Pause

	pause.Update();

	// Stats
	featureMenu.Update();
	//bool activad = false;
	//if (app->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
	//{
	//	activad = !activad;
	//}
	//
	////La textura ya esta aplicada, aplicar un v2V
	//app->render->DrawTexture(Juan,0,0);
	//if (app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN)
	//{
	//	Juan_anim.crear_Animation(Juan, {15,15}, { 500,500 }, activad);
	//}
	//


	return true;
}

// Called each loop iteration
bool SceneGameplay::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;

	// Pause

	pause.PostUpdate();

	//Player

	if (player->godMode == true)
	{

		app->render->DrawText("GODMODE", 100, 100, 90, 40, { 255, 255, 255, 255 });
		app->render->DrawText("1. Maps", 150, 150, 60, 20, { 255, 255, 255, 255 });
		
		if (map_selector == true && actually == 0)
		{
			app->render->DrawText("1. Mapa Jovani", 260, 150, 125, 20, { 255, 255, 255, 255 });
			app->render->DrawText("2. Mapa Cofre", 260, 180, 108, 20, { 255, 255, 255, 255 });
		}
		if (map_selector == true && actually == 1)
		{
			app->render->DrawText("1. Mapa Mazmorra", 260, 150, 142, 20, { 255, 255, 255, 255 });
			app->render->DrawText("2. Mapa Cofre", 260, 180, 108, 20, { 255, 255, 255, 255 });
		}
		if (map_selector == true && actually == 2)
		{
			app->render->DrawText("1. Mapa Mazmorra", 260, 150, 142, 20, { 255, 255, 255, 255 });
			app->render->DrawText("2. Mapa Jovani", 260, 180, 125, 20, { 255, 255, 255, 255 });
		}
	}

	if (pause.Exit->state == GuiControlState::PRESSED) ret = false;

	// Stats
	
	featureMenu.PostUpdate();

	return ret;
}

// Called before quitting
bool SceneGameplay::CleanUp()
{
	LOG("Freeing scene");
	//app->map->CleanUp();
	//app->physics->CleanUp();
	return true;
}

bool SceneGameplay::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}

