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
#include "EntityManager.h"

#include "SceneGameplay.h"

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

	}

	for (pugi::xml_node enemyNode = config.child("enemy"); enemyNode; enemyNode = enemyNode.next_sibling("enemy"))
	{
		Enemy* enemy = (Enemy*)app->entityManager->CreateEntity(EntityType::ENEMY);
		enemy->parameters = enemyNode;

		enemies.Add(enemy);

	}

	return true;
}

// Called before the first frame
bool SceneGameplay::Start()
{
	app->map->actualmap = 0;

	bool retLoad = app->map->Load();
	//app->map->Enable();

	enableMusic = true;
	
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
		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && actually == 0)
		{
			app->map->CleanUp();
			app->map->actualmap = 2;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 2;
		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && actually == 1)
		{

			app->map->CleanUp();
			app->map->actualmap = 0;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 0;
		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && actually == 1)
		{

			app->map->CleanUp();
			app->map->actualmap = 2;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 2;
		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN && actually == 2)
		{
			app->map->CleanUp();
			app->map->actualmap = 0;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 0;
		}
		if (map_selector == true && app->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN && actually == 2)
		{
			app->map->CleanUp();
			app->map->actualmap = 1;
			bool retLoad = app->map->Load();
			map_selector = false;
			actually = 1;
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

	return true;
}

// Called each loop iteration
bool SceneGameplay::PostUpdate()
{
	OPTICK_EVENT();
	if (player->godMode == true)
	{
		app->render->DrawText("GODMODE", 100, 100, 150, 60, { 255, 255, 255, 255 });
		app->render->DrawText("1. Maps", 150, 150, 90, 45, { 255, 255, 255, 255 });
		
		if (map_selector == true && actually == 0)
		{
			app->render->DrawText("1. Mapa Jovani", 260, 150, 140, 45, { 255, 255, 255, 255 });
			app->render->DrawText("2. Mapa Cofre", 260, 180, 140, 45, { 255, 255, 255, 255 });
		}
		if (map_selector == true && actually == 1)
		{
			app->render->DrawText("1. Mapa Mazmorra", 260, 150, 160, 45, { 255, 255, 255, 255 });
			app->render->DrawText("2. Mapa Cofre", 260, 180, 140, 45, { 255, 255, 255, 255 });
		}
		if (map_selector == true && actually == 2)
		{
			app->render->DrawText("1. Mapa Mazmorra", 260, 150, 160, 45, { 255, 255, 255, 255 });
			app->render->DrawText("2. Mapa Jovani", 260, 180, 140, 45, { 255, 255, 255, 255 });
		}
	}

	bool ret = true;

	

	return true;
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