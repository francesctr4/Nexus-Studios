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
#include "Mapa_Infierno.h"

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

	if (app->map->actualmap == 6 && Tp_Puzzle_1 == true)
	{
		TP_Infierno_4 = app->physics->CreateRectangleSensor(1280, 210, 9, 95, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_4 = false;
	}
	if (app->map->actualmap == 7 && Tp_Puzzle_2 == true)
	{
		TP_Infierno_Jovani = app->physics->CreateRectangleSensor(610, 0, 95, 9, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_Jovani = false;
	}

	if (app->map->actualmap == 8 && Tp_Puzzle_3 == true)
	{
		TP_Infierno_Jovani = app->physics->CreateRectangleSensor(610, 0, 20, 9, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_Jovani = false;
	}
	//Puzzle3
	if (app->map->actualmap == 4 && Tp_4 == true)
	{
		TP_Infierno_Jovani = app->physics->CreateRectangleSensor(610, 0, 20, 9, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_4 = false;
	}
	//BossFinal
	if (app->map->actualmap == 5 && Tp_5 == true)
	{
		TP_Infierno_Jovani = app->physics->CreateRectangleSensor(960,80, 20, 20, bodyType::KINEMATIC, ColliderType::TELEPORT_INFIERNO);
		Tp_5 = false;
	}

	// Go to Ending Screen

	if (app->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) {

		app->audio->PlayFx(endingScreenFX);
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

		app->render->DrawText("GODMODE", 100, 100, 130, 80, { 255, 255, 255, 255 });
		app->render->DrawText("1. Maps", 150, 165, 85, 50, { 255, 255, 255, 255 });
		
		if (map_selector == true)
		{
			app->render->DrawText("2- Mapa Infierno", 245, 170, 160, 45, { 255, 255, 255, 255 });
			if(infierno == true)
			{
				app->render->DrawText("0- 1st Room", 420, 180, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("1- 2nd Room", 420, 210, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("2- 3rd Room", 420, 240, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("3- 4th Room", 420, 270, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("4- 5th Room", 420, 300, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("5- 6th Room", 420, 330, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("6- 7th Room", 420, 360, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("7- Chest", 420, 390, 125, 20, { 255, 255, 255, 255 });
				app->render->DrawText("8- Jovani Room", 420, 420, 125, 20, { 255, 255, 255, 255 });
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

