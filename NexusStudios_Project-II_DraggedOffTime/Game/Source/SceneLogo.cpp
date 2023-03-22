#include "App.h"
#include "Defs.h"
#include "Log.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"

#include "SceneLogo.h"

SceneLogo::SceneLogo()
{
	name.Create("sceneEnding");
}

// Destructor
SceneLogo::~SceneLogo()
{}

// Called before the first frame
bool SceneLogo::Start()
{

	return true;
}

// Called each loop iteration
bool SceneLogo::PreUpdate()
{
	OPTICK_EVENT();

	return true;
}

// Called each loop iteration
bool SceneLogo::Update(float dt)
{
	OPTICK_EVENT();

	if (app->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN) {

		TransitionToScene(SceneType::TITLE);

	}

	SDL_Rect rect = { 0,0, 1024, 768 };
	app->render->DrawRectangle(rect, 255, 0, 0, 150);

	return true;
}

// Called each loop iteration
bool SceneLogo::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;



	return true;
}

// Called before quitting
bool SceneLogo::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool SceneLogo::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}