#include "App.h"
#include "Defs.h"
#include "Log.h"

#include "SDL_mixer/include/SDL_mixer.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Map.h"

#include "Scene.h"
#include "SceneManager.h"

#include "SceneLogo.h"
#include "SceneTitle.h"
#include "SceneGameplay.h"
#include "SceneBattle.h"

#define FADEOUT_TRANSITION_SPEED	2.0f
#define FADEIN_TRANSITION_SPEED		2.0f

SceneManager::SceneManager(bool startEnabled) : Module(startEnabled)
{
	name.Create("scene");

	current = new SceneLogo();
	next = nullptr;

	onTransition = false;
	fadeOutCompleted = false;
	transitionAlpha = 0;
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
	current->Start();
	
	return true;
}

// Called each loop iteration
bool SceneManager::PreUpdate()
{
	OPTICK_EVENT();

	current->PreUpdate();

	return true;
}

// Called each loop iteration
bool SceneManager::Update(float dt)
{
	OPTICK_EVENT();

	dt = dt / 1000;
	app->map->Init();
	LOG("Updating Current Scene");
	bool ret = true;

	if (!onTransition)
	{
		ret = current->Update(dt);
	}
	else
	{
		if (!fadeOutCompleted)
		{
			transitionAlpha += (FADEOUT_TRANSITION_SPEED * dt);

			// NOTE: Due to float internal representation, condition jumps on 1.0f instead of 1.05f
			// For that reason we compare against 1.01f, to avoid last frame loading stop
			if (transitionAlpha > 1.01f)
			{
				transitionAlpha = 1.0f;

				current->CleanUp();	// Unload current screen
				next->Start();	// Load next screen

				delete current;	// Free current pointer
				current = next;	// Assign next pointer
				next = nullptr;

				// Activate fade out effect to next loaded screen
				fadeOutCompleted = true;
			}
		}
		else  // Transition fade out logic
		{
			transitionAlpha -= (FADEIN_TRANSITION_SPEED * dt);

			if (transitionAlpha < -0.01f)
			{
				transitionAlpha = 0.0f;
				fadeOutCompleted = false;
				onTransition = false;
			}
		}
	}

	// Draw current scene
	current->Update(dt);

	// Draw full screen rectangle in front of everything
	if (onTransition)
	{
		app->render->DrawRectangle({ 0, 0, 1280, 720 }, 0, 0, 0, (unsigned char)(255.0f * transitionAlpha));
	}

	if (current->transitionRequired)
	{
		onTransition = true;
		fadeOutCompleted = false;
		transitionAlpha = 0.0f;

		switch (current->nextScene)
		{
			case SceneType::NONE: 
				next = nullptr; 
				break;

			case SceneType::LOGO: 
				next = new SceneLogo(); 
				break;

			case SceneType::TITLE: 
				next = new SceneTitle(); 
				break;

			case SceneType::GAMEPLAY: 
				next = new SceneGameplay(); 
				break;

			case SceneType::BATTLE: 
				next = new SceneBattle(); 
				break;

			default: 
				break;
		}

		current->transitionRequired = false;

	}

	return ret;
}

// Called each loop iteration
bool SceneManager::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;

	current->PostUpdate();

	return ret;
}

// Called before quitting
bool SceneManager::CleanUp()
{
	LOG("Freeing scene");

	current->CleanUp();

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