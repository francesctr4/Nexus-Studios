#include "App.h"
#include "Defs.h"
#include "Log.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"
#include "PathFinding.h"
#include "SceneManager.h"
#include "Player.h"

#include "SceneLogo.h"

SceneLogo::SceneLogo()
{
	name.Create("sceneEnding");
	
}

// Destructor
SceneLogo::~SceneLogo()
{}

bool SceneLogo::Awake()
{

	return true;
}

// Called before the first frame
bool SceneLogo::Start()
{
	app->map->actualmap = 0;

	bool retLoad = app->map->Load();
	

	/*if (retLoad) {
		int w, h;
		uchar* data = NULL;

		bool retWalkMap = app->map->CreateWalkabilityMap(w, h, &data);
		if (retWalkMap) app->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);

	}*/

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
	
	app->map->Draw();
	
	
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
	
	app->map->CleanUp();


	return true;
}

bool SceneLogo::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}