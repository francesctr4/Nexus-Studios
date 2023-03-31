#include "App.h"
#include "Defs.h"
#include "Log.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneManager.h"
#include "Map.h"

#include "SceneTitle.h"

SceneTitle::SceneTitle()
{
	name.Create("sceneEnding");
}

// Destructor
SceneTitle::~SceneTitle()
{}

// Called before the first frame
bool SceneTitle::Start()
{
	app->map->actualmap = 1;

	
	bool retLoad = app->map->Load();
	app->map->Enable();
	

	return true;
}

// Called each loop iteration
bool SceneTitle::PreUpdate()
{
	OPTICK_EVENT();

	return true;
}

// Called each loop iteration
bool SceneTitle::Update(float dt)
{
	OPTICK_EVENT();

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {

		TransitionToScene(SceneType::GAMEPLAY);

	}

	app->map->Draw();

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

	app->map->Disable();

	return true;
}

bool SceneTitle::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}