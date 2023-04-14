#include "App.h"
#include "Defs.h"
#include "Log.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "EntityManager.h"

#include "SceneGameplay.h"

SceneGameplay::SceneGameplay()
{
	name.Create("sceneGameplay");
	this->Awake();
}

// Destructor
SceneGameplay::~SceneGameplay()
{}

bool SceneGameplay::Awake()
{

	player = (Player*)app->entityManager->CreateEntity(EntityType::PLAYER);
	player->parameters = app->configNode.child("sceneGameplay").child("player");

	return true;
}

// Called before the first frame
bool SceneGameplay::Start()
{
	//5app->map->actualmap = 2;


	bool retLoad = app->map->Load();
	app->map->Enable();
	
	return true;
}

// Called each loop iteration
bool SceneGameplay::PreUpdate()
{
	OPTICK_EVENT();

	return true;
}

// Called each loop iteration
bool SceneGameplay::Update(float dt)
{
	OPTICK_EVENT();

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {

		TransitionToScene(SceneType::BATTLE);

	}

	app->map->Draw();
	/*SDL_Rect rect = { 0,0, 1280, 720 };
	app->render->DrawRectangle(rect, 255, 255, 255, 150);*/

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
	app->map->CleanUp();
	app->physics->CleanUp();
	return true;
}

bool SceneGameplay::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}