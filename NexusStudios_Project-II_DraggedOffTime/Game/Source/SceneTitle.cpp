#include "App.h"
#include "Defs.h"
#include "Log.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"

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

	SDL_Rect rect = { 0,0, 1280, 720 };
	app->render->DrawRectangle(rect, 0, 255, 0, 255);

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

	return true;
}

bool SceneTitle::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}