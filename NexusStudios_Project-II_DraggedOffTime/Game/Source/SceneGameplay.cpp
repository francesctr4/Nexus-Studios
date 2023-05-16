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
#include "QuestManager.h"

#include "SceneGameplay.h"
#include "Puzzle1.h"

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

		npcs.push_back(npc);

	}

	for (pugi::xml_node enemyNode = config.child("enemy"); enemyNode; enemyNode = enemyNode.next_sibling("enemy"))
	{
		Enemy* enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
		enemy->parameters = enemyNode;

		enemies.push_back(enemy);

	}

	for (pugi::xml_node itemNode = config.child("item"); itemNode; itemNode = itemNode.next_sibling("item"))
	{
		Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
		item->parameters = itemNode;

		items.push_back(item);

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

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {

		app->SaveGameRequest();

		app->sceneTitle->continueEnabled = true;

	}

	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();

	//Player

	if (player->godMode == true)
	{
		
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN )
		{
			
			app->map->CleanUp();
			app->map->actualmap = 0;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(200, 671);

			//Move Npcs Map_1
			npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			
			npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			
			npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);
			npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);

			//Move Enemies Map_1
			enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			
			enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);


		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{

			app->map->CleanUp();
			app->map->actualmap = 1;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(650, 700);

			//Move Npcs Map_1
			npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);
			npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(650),PIXEL_TO_METERS(260) }, 0);

			//Move Enemies Map_1
			enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);


		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			app->map->CleanUp();
			app->map->actualmap = 2;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(1265, 560);
			
			//Move Npcs Map_2
			npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			//Move Enemies Map_2
			enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
		}
	
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		{

			app->map->CleanUp();
			app->map->actualmap = 3;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(1255, 106);
			
			//Move Npcs Map_3
			npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			//Move Enemies Map_3
			enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		}

		if (infierno == true && app->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
		{

			app->map->CleanUp();
			app->map->actualmap = 4;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(650, 700);

			//Move Npcs Map_3
			npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			//Move Enemies Map_3
			enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		}

		if (infierno == true && app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN)
		{
			app->map->CleanUp();
			app->map->actualmap = 5;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(650, 700);

			//Move Npcs Map_3
			npcs.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(0)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(1)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			npcs.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			npcs.at(2)->npcSensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			//Move Enemies Map_3
			enemies.at(0)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(0)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(1)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(1)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(2)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);
			enemies.at(2)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(123297) }, 0);

			enemies.at(3)->pbody->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
			enemies.at(3)->enemySensor->body->SetTransform({ PIXEL_TO_METERS(834752),PIXEL_TO_METERS(834752) }, 0);
		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_6) == KEY_DOWN)
		{
			app->map->CleanUp();
			app->map->actualmap = 6;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(650, 700);
		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_7) == KEY_DOWN)
		{
			app->map->CleanUp();
			app->map->actualmap = 7;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(650, 700);
			
		}
		if (infierno == true && app->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
		{
			app->map->CleanUp();
			app->map->actualmap = 8;
			bool retLoad = app->map->Load();
			infierno = false;
			app->sceneGameplay->player->Teleport(650, 700);
		}

		if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && infierno == false)
		{
			map_selector = !map_selector;
		}
		if (app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			infierno = !infierno;
		}
		if (app->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN && infierno == true)
		{
			infierno = false;
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

	//Quests
	CheckEvent();
	//Ya va

	// Puzzles
	if (app->map->actualmap == 6) {

		if (puzzle3.canLoad) {

			puzzle3.Load();
			puzzle3.canLoad = false;
		}

		puzzle3.Update();
		puzzle3.canClean = true;
	}
	else if (puzzle3.canClean == true && app->map->actualmap != 6) {

		puzzle3.canClean = false;
		puzzle3.canLoad = true;
	}


	if (app->map->actualmap == 7) {

		if (puzzle2.canLoad) {

			puzzle2.Load();
			puzzle2.canLoad = false;
		}
		
		puzzle2.Update();
		puzzle2.canClean = true;
	} 
	else if(puzzle2.canClean == true && app->map->actualmap != 7){

		puzzle2.CleanUp();
		puzzle2.canClean = false;
		puzzle2.canLoad = true;
	}


	if (app->map->actualmap == 6) {

		if (puzzle1.canLoad) {

			puzzle1.Load();
			puzzle1.canLoad = false;
		}

		puzzle1.Update();
		puzzle1.canClean = true;
	}
	else if (puzzle1.canClean == true && app->map->actualmap != 6) {

		puzzle1.CleanUp();
		puzzle1.canClean = false;
		puzzle1.canLoad = true;
	}
	
	

	//Charge all the sensors on the different maps
	if (app->map->actualmap == 0 && Tp_0 == true)
	{
		TP_Infierno_0 = app->physics->CreateRectangleSensor(1168, 365, 50, 50, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_0 = false;
	}
	
	if (app->map->actualmap == 1 && Tp_1 == true)
	{
		TP_Infierno_1 = app->physics->CreateRectangleSensor(0, 550, 9, 95, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_1 = false;
	}
	if (app->map->actualmap == 2 && Tp_2 == true)
	{
		TP_Infierno_2 = app->physics->CreateRectangleSensor(0, 350, 9, 95, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_2 = false;
	}
	
	if (app->map->actualmap == 3 && Tp_3 == true)
	{
		TP_Infierno_3 = app->physics->CreateRectangleSensor(1273, 590, 9, 95, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_3 = false;
		
	}

	if (app->map->actualmap == 3 && Tp_Cofre == true)
	{
		TP_Infierno_Cofre = app->physics->CreateRectangleSensor(1180, 255, 20, 9, bodyType::KINEMATIC, ColliderType::TELEPORT_JOVANI);
		Tp_Cofre = false;
	}
	//Puzzle1
	if (app->map->actualmap == 4 && Tp_4 == true)
	{
		TP_Infierno_4 = app->physics->CreateRectangleSensor(1180, 255, 20, 9, bodyType::KINEMATIC, ColliderType::TELEPORT_JOVANI);
		Tp_4 = false;
	}
	if (app->map->actualmap == 4 && Tp_Jovani == true)
	{
		TP_Infierno_Jovani = app->physics->CreateRectangleSensor(1180, 255, 20, 9, bodyType::KINEMATIC, ColliderType::TELEPORT_JOVANI);
		Tp_Jovani = false;
	}
	//Puzzle2
	if (app->map->actualmap == 4 && Tp_Jovani == true)
	{
		TP_Infierno_Jovani = app->physics->CreateRectangleSensor(1180, 255, 20, 9, bodyType::KINEMATIC, ColliderType::TELEPORT_JOVANI);
		Tp_Jovani = false;
	}
	//Puzzle3
	if (app->map->actualmap == 4 && Tp_Jovani == true)
	{
		TP_Infierno_Jovani = app->physics->CreateRectangleSensor(1180, 255, 20, 9, bodyType::KINEMATIC, ColliderType::TELEPORT_JOVANI);
		Tp_Jovani = false;
	}
	//BossFinal
	if (app->map->actualmap == 4 && Tp_Jovani == true)
	{
		TP_Infierno_Jovani = app->physics->CreateRectangleSensor(1180, 255, 20, 9, bodyType::KINEMATIC, ColliderType::TELEPORT_JOVANI);
		Tp_Jovani = false;
	}

	// Go to Ending Screen

	if (app->input->GetKey(SDL_SCANCODE_0) == KEY_DOWN) {

		app->fadeToBlack->Fade(this, (Module*)app->sceneEnding);

	}

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
		
		if (map_selector == true)
		{
			app->render->DrawText("Mapa Infierno", 260, 150, 125, 20, { 255, 255, 255, 255 });
			if(infierno == true)
			{
				app->render->DrawText("   1st Room", 400, 150, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("   2nd Room", 400, 180, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("   3st Room", 400, 210, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("   4th Room", 400, 240, 125, 20, { 255, 255, 255, 255 });
			}
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
	control->timePressed.Start();

	if (featureMenu.ShowSlots) {

		featureMenu.inventoryManager.RemoveCertainItem(control->id);

	}

	return true;
}

//Función dedicada a comprobar en todo momento si hay alguna misión completada
void SceneGameplay::CheckEvent()
{
	//Check the variables
	if (trigger_1 == true)
	{
		first_mision = true;
	}

	if (trigger_2 == 8)
	{
		second_mision = true;
	}

	if (trigger_3 == true)
	{
		third_mision = true;
	}
	//------------

	for (std::list <Quest*>::iterator it = app->questManager->active_quests.begin(); it != app->questManager->active_quests.end(); it++)
	{
		int quest_id = (*it)->id;

		switch (quest_id)
		{
		case 1:
			if (first_mision == true && second_mision == true && third_mision == true && r >= 0)
			{
				(*it)->completed = true;
				r = 1;
				LOG("R: %d", r);
				////Reset variables
				//this->trigger_1 = 0;
				//this->trigger_2 = 0;
				//this->trigger_3 = 0;
				//first_mision = false;
				//second_mision = false;
				//third_mision = false;
				//------------
				app->questManager->finished_quests.push_back((*it));
				app->questManager->active_quests.erase(it);
			}
			break;
		case 2:
			if (first_mision == true && second_mision == true && third_mision == true && r >= 1)
			{
				(*it)->completed = true;
				r = 2;
				LOG("R: %d", r);
				////Reset variables
				//this->trigger_1 = 0;
				//this->trigger_2 = 0;
				//this->trigger_3 = 0;
				//first_mision = false;
				//second_mision = false;
				//third_mision = false;
				//------------
				app->questManager->finished_quests.push_back((*it));
				app->questManager->active_quests.erase(it);
			}
			break;
		case 3:
			if (first_mision == true && second_mision == true && third_mision == true && r >= 1)
			{
				(*it)->completed = true;
				r = 3;
				LOG("R: %d", r);
				////Reset variables
				//this->trigger_1 = 0;
				//this->trigger_2 = 0;
				//this->trigger_3 = 0;
				//first_mision = false;
				//second_mision = false;
				//third_mision = false;
				//------------
				app->questManager->finished_quests.push_back((*it));
				app->questManager->active_quests.erase(it);

			}
			break;
		default:
			break;
		}
	}
}

