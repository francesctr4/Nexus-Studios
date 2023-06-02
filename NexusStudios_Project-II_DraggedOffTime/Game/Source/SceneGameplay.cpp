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
#include "Infierno.h"

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

	/*for (pugi::xml_node npcNode = config.child("npc"); npcNode; npcNode = npcNode.next_sibling("npc"))
	{
		NPC* npc = (NPC*)app->entityManager->CreateEntity(EntityType::NPC);
		npc->parameters = npcNode;

		npcs.push_back(npc);
	}*/

	//for (pugi::xml_node enemyNode = config.child("enemy"); enemyNode; enemyNode = enemyNode.next_sibling("enemy"))
	//{
	//	Enemy* enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
	//	enemy->parameters = enemyNode;

	//	enemies.push_back(enemy);

	//}

	/*for (pugi::xml_node itemNode = config.child("item"); itemNode; itemNode = itemNode.next_sibling("item"))
	{
		Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
		item->parameters = itemNode;

		items.push_back(item);

	}*/

	xml_node = config;
	
	return true;
}

void LoadMapEntities()
{
	
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

	endingScreenFX = app->audio->LoadFx("Assets/Audio/Fx/EndingScreen.wav");

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

	if (app->input->GetKey(SDL_SCANCODE_8) == KEY_DOWN)
	{
		int mx, my;
		app->input->GetMousePosition(mx, my);
		fPoint pos((float)mx, (float)my);
		eWave_1 = app->particleSystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_WAVE_1);
		eBurst_1 = app->particleSystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_BURST);
	}

	if (app->input->GetKey(SDL_SCANCODE_9) == KEY_DOWN)
	{
		fPoint pos((float)app->sceneGameplay->player->position.x + 16, (float)app->sceneGameplay->player->position.y + 16);
		eWave_2 = app->particleSystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_WAVE_2);
		eBurst_2 = app->particleSystem->AddEmiter(pos, EmitterType::EMITTER_TYPE_BURST);
	}

	if (app->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN) {

		app->SaveGameRequest();

		app->sceneTitle->continueEnabled = true;

	}

	if (app->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		app->LoadGameRequest();


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


	if (app->map->actualmap == 8) {

		if (puzzle1.canLoad) {

			puzzle1.Load();
			puzzle1.canLoad = false;
		}

		puzzle1.Update();
		puzzle1.canClean = true;
	}
	else if (puzzle1.canClean == true && app->map->actualmap != 8) {

		puzzle1.CleanUp();
		puzzle1.canClean = false;
		puzzle1.canLoad = true;
	}
	
	// Go to Ending Screen

	if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {

		app->audio->PlayFx(endingScreenFX);
		app->fadeToBlack->Fade(this, (Module*)app->sceneEnding);

	}
	mapa_Infierno.Update();
	
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

	if (pause.Exit->state == GuiControlState::PRESSED) ret = false;

	// Stats
	
	featureMenu.PostUpdate();

	return ret;
}

// Called before quitting
bool SceneGameplay::CleanUp()
{
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

void SceneGameplay::LoadMapEntities(int map)
{
	
	for (pugi::xml_node npcNode = xml_node.child("npc"); npcNode; npcNode = npcNode.next_sibling("npc"))
	{
		int aparicion = npcNode.attribute("map").as_int();

		if (aparicion == map)
		{
			NPC* npc = (NPC*)app->entityManager->CreateEntity(EntityType::NPC);
			npc->parameters = npcNode;
			npc->Awake();
			npc->Start();
			npcs.push_back(npc);
		}
	}

	for (pugi::xml_node enemyNode = xml_node.child("enemy"); enemyNode; enemyNode = enemyNode.next_sibling("enemy"))
	{
		int aparicion = enemyNode.attribute("map").as_int();

		if (aparicion == map)
		{
			Enemy* enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
			enemy->parameters = enemyNode;
			enemy->Awake();
			enemy->Start();

			enemies.push_back(enemy);
		}
	}

	for (pugi::xml_node itemNode = xml_node.child("item"); itemNode; itemNode = itemNode.next_sibling("item"))
	{
		int aparicion = itemNode.attribute("map").as_int();

		if (aparicion == map)
		{
			Item* item = (Item*)app->entityManager->CreateEntity(EntityType::ITEM);
			item->parameters = itemNode;
			item->Awake();
			item->Start();
			items.push_back(item);
		}
	}
}

void SceneGameplay::UnloadMapEntities()
{
	for (std::vector<Enemy*>::iterator it = enemies.begin(); it != enemies.end(); ++it) 
	{
		app->entityManager->DestroyEntity(*it);
	}

	enemies.clear();

	for (std::vector<NPC*>::iterator it = npcs.begin(); it != npcs.end(); ++it)
	{
		app->entityManager->DestroyEntity(*it);
	}

	npcs.clear();
	
	for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); ++it)
	{
		app->entityManager->DestroyEntity(*it);
	}

	items.clear();
}

bool SceneGameplay::IsAnyNpcDialogueActivated()
{

	for (std::vector<NPC*>::iterator it = npcs.begin(); it != npcs.end(); ++it)
	{
		if ((*it)->dialogueActivated)
		{
			return true;
		}
	}

	
	return false;
}

void SceneGameplay::LoadMap(int map)
{
	app->map->CleanUp();
	app->sceneGameplay->UnloadMapEntities();
	app->map->actualmap = map;
	app->map->Load();
	app->sceneGameplay->LoadMapEntities(map);

}

