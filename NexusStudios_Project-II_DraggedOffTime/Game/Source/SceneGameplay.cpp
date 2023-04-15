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

	return true;
}

// Called before the first frame
bool SceneGameplay::Start()
{
	//5app->map->actualmap = 2;


	/*bool retLoad = app->map->Load();
	app->map->Enable();*/

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

	if (app->input->GetKey(SDL_SCANCODE_5) == KEY_DOWN) {

		if (app->physics->debug) app->physics->debug = false;
		else app->physics->debug = true;

	}

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {

		//TransitionToScene(SceneType::BATTLE);
		enableMusic = true;
		app->fadeToBlack->Fade(this, (Module*)app->sceneBattle);

	}

	//app->map->Draw();
	SDL_Rect rect = { 0,0, 1280, 720 };
	app->render->DrawRectangle(rect, 125, 255, 125);

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