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

	if (!app->entityManager->IsEnabled()) {

		app->entityManager->Enable();

	}

	if (app->sceneGameplay->player->godMode) app->physics->debug = true;
	else app->physics->debug = false;

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) {

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

	bool ret = true;

	

	return true;
}

// Called before quitting
bool SceneGameplay::CleanUp()
{
	LOG("Freeing scene");
	/*app->map->CleanUp();
	app->physics->CleanUp();*/
	return true;
}

bool SceneGameplay::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}