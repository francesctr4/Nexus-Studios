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
#include "FadeToBlack.h"
#include "EntityManager.h"
#include "Player.h"

#include "SceneLore.h"

SceneLore::SceneLore(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneLore");

	enableMusic = true;

}

// Destructor
SceneLore::~SceneLore()
{}

bool SceneLore::Awake(pugi::xml_node& config)
{

	return true;
}

// Called before the first frame
bool SceneLore::Start()
{

	return true;
}

// Called each loop iteration
bool SceneLore::PreUpdate()
{
	OPTICK_EVENT();

	app->entityManager->Disable();

	if (enableMusic) {

		app->audio->PlayMusic("Assets/Audio/Music/NoMusic.ogg", 0);
		enableMusic = false;

	}

	return true;
}

// Called each loop iteration
bool SceneLore::Update(float dt)
{
	OPTICK_EVENT();

	app->render->DrawText("LORE DRAGGED OFF TIME", 200, 300, 900, 90, { 255,255,255 });

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) {

		enableMusic = true;
		app->fadeToBlack->Fade(this, reinterpret_cast<Module*>(app->sceneGameplay));
	}

	return true;
}

// Called each loop iteration
bool SceneLore::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_BACK] == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool SceneLore::CleanUp()
{

	return true;
}

bool SceneLore::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}