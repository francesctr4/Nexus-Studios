#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneLogo.h"
#include "EntityManager.h"
#include "Map.h"
#include "Physics.h"
#include "FadeToBlack.h"

#include "Defs.h"
#include "Log.h"

SceneLogo::SceneLogo(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneLogo");
}

// Destructor
SceneLogo::~SceneLogo()
{}

// Called before render is available
bool SceneLogo::Awake(pugi::xml_node& config)
{
	LOG("Loading SceneLogo");
	bool ret = true;

	return ret;
}

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

	return true;
}

// Called each loop iteration
bool SceneLogo::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;

	return ret;
}

// Called before quitting
bool SceneLogo::CleanUp()
{
	LOG("Freeing scene");

	return true;
}