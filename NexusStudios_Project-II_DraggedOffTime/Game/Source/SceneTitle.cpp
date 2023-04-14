#include "App.h"
#include "Defs.h"
#include "Log.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Physics.h"
#include "FadeToBlack.h"
#include "EntityManager.h"
#include "Map.h"

#include "SceneTitle.h"

SceneTitle::SceneTitle(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneTitle");
}

// Destructor
SceneTitle::~SceneTitle()
{}

bool SceneTitle::Awake(pugi::xml_node& config)
{

	return true;
}

// Called before the first frame
bool SceneTitle::Start()
{

	//app->map->actualmap = 1;

	return true;
}

// Called each loop iteration
bool SceneTitle::PreUpdate()
{
	OPTICK_EVENT();
	app->entityManager->Disable();

	return true;
}

// Called each loop iteration
bool SceneTitle::Update(float dt)
{
	OPTICK_EVENT();

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {

		//TransitionToScene(SceneType::GAMEPLAY);
		app->fadeToBlack->Fade(this, (Module*)app->sceneGameplay);
	}

	SDL_Rect rect = { 0,0, 1280, 720 };
	app->render->DrawRectangle(rect, 0, 0, 255, 150);

	//app->map->Draw();

	return true;
}

// Called each loop iteration
bool SceneTitle::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;

	

	return true;
}

// Called before quitting
bool SceneTitle::CleanUp()
{
	LOG("Freeing scene");

	//app->map->CleanUp();

	return true;
}

bool SceneTitle::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}