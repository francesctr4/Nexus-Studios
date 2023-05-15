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
		
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN )
		{
			
			app->map->CleanUp();
			app->map->actualmap = 0;
			bool retLoad = app->map->Load();
			map_selector = false;
			app->sceneGameplay->player->Teleport(150, 430);

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
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
		{
			app->map->CleanUp();
			app->map->actualmap = 1;
			bool retLoad = app->map->Load();
			map_selector = false;
			app->sceneGameplay->player->Teleport(25, 560);
			
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
	
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
		{

			app->map->CleanUp();
			app->map->actualmap = 2;
			bool retLoad = app->map->Load();
			map_selector = false;
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
		
		if (app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
		{
			map_selector = !map_selector;
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
			app->render->DrawText("1. Mapa Infierno", 260, 150, 125, 20, { 255, 255, 255, 255 });
			app->render->DrawText("2. Mapa Cofre", 260, 180, 108, 20, { 255, 255, 255, 255 });
		}
		if (map_selector == true && actually == 1)
		{
			app->render->DrawText("1. Mapa Infierno", 260, 150, 142, 20, { 255, 255, 255, 255 });
			app->render->DrawText("2. Mapa Cofre", 260, 180, 108, 20, { 255, 255, 255, 255 });
		}
		if (map_selector == true && actually == 2)
		{
			app->render->DrawText("1. Mapa Infierno", 260, 150, 142, 20, { 255, 255, 255, 255 });
			app->render->DrawText("2. Mapa Cofre", 260, 180, 125, 20, { 255, 255, 255, 255 });
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

