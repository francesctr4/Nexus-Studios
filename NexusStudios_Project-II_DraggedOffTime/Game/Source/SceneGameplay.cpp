#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneGameplay.h"
#include "EntityManager.h"
#include "Map.h"
#include "Physics.h"
#include "FadeToBlack.h"

#include "Defs.h"
#include "Log.h"

SceneGameplay::SceneGameplay()
{
	name.Create("sceneEnding");
}

// Destructor
SceneGameplay::~SceneGameplay()
{}

// Called before the first frame
bool SceneGameplay::Start()
{

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

	if (app->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN) {

		TransitionToScene(SceneType::TITLE);

	}

	SDL_Rect rect = { 0,0, 1024, 768 };
	app->render->DrawRectangle(rect, 255, 255, 255, 150);

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

	return true;
}

bool SceneGameplay::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}