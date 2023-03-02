#include "App.h"
#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "SceneEnding.h"
#include "EntityManager.h"
#include "Map.h"
#include "Physics.h"
#include "FadeToBlack.h"

#include "Defs.h"
#include "Log.h"

SceneEnding::SceneEnding(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneEnding");
}

// Destructor
SceneEnding::~SceneEnding()
{}

// Called before render is available
bool SceneEnding::Awake(pugi::xml_node& config)
{
	LOG("Loading SceneLogo");
	bool ret = true;


	return ret;
}

// Called before the first frame
bool SceneEnding::Start()
{

	return true;
}

// Called each loop iteration
bool SceneEnding::PreUpdate()
{
	

	return true;
}

// Called each loop iteration
bool SceneEnding::Update(float dt)
{


	return true;
}

// Called each loop iteration
bool SceneEnding::PostUpdate()
{
	bool ret = true;

	return ret;
}

// Called before quitting
bool SceneEnding::CleanUp()
{
	LOG("Freeing scene");

	return true;
}