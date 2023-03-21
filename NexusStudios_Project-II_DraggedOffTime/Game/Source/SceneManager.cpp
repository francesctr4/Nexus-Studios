#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneManager.h"
#include "EntityManager.h"
#include "Map.h"
#include "Physics.h"
#include "FadeToBlack.h"
#include "Fonts.h"
#include "Pathfinding.h"
#include "SceneTitle.h"
#include "Scene.h"

#include "Defs.h"
#include "Log.h"

#include "SDL_mixer/include/SDL_mixer.h"

#define FADEOUT_TRANSITION_SPEED	2.0f
#define FADEIN_TRANSITION_SPEED		2.0f

SceneManager::SceneManager(bool startEnabled) : Module(startEnabled)
{
	name.Create("scene");
}

// Destructor
SceneManager::~SceneManager()
{}

// Called before render is available
bool SceneManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;



	return ret;
}

// Called before the first frame
bool SceneManager::Start()
{



	return true;
}

// Called each loop iteration
bool SceneManager::PreUpdate()
{
	OPTICK_EVENT();

	return true;
}

// Called each loop iteration
bool SceneManager::Update(float dt)
{
	OPTICK_EVENT();

	return true;
}

// Called each loop iteration
bool SceneManager::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;

	return ret;
}

// Called before quitting
bool SceneManager::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

bool SceneManager::LoadState(pugi::xml_node& load)
{
	

	return true;
}

bool SceneManager::SaveState(pugi::xml_node& save)
{
	

	return true;
}