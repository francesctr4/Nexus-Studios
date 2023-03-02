#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Scene.h"
#include "EntityManager.h"
#include "Map.h"
#include "Physics.h"
#include "FadeToBlack.h"
#include "Fonts.h"
#include "Pathfinding.h"
#include "SceneTitle.h"

#include "Defs.h"
#include "Log.h"

#include "SDL_mixer/include/SDL_mixer.h"

Scene::Scene(bool startEnabled) : Module(startEnabled)
{
	name.Create("scene");
}

// Destructor
Scene::~Scene()
{}

// Called before render is available
bool Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");
	bool ret = true;



	return ret;
}

// Called before the first frame
bool Scene::Start()
{
	
	

	return true;
}

// Called each loop iteration
bool Scene::PreUpdate()
{
	OPTICK_EVENT();

	return true;
}

// Called each loop iteration
bool Scene::Update(float dt)
{
	OPTICK_EVENT();

	return true;
}

// Called each loop iteration
bool Scene::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;

	return ret;
}

// Called before quitting
bool Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
