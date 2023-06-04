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

#include "SceneEnding.h"
#include "SceneGameplay.h"

SceneEnding::SceneEnding(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneEnding");

	enableMusic = true;

	endingScreen = nullptr;
	currentAnimation = nullptr;

}

// Destructor
SceneEnding::~SceneEnding()
{}

bool SceneEnding::Awake(pugi::xml_node& config)
{

	for (int i = 0; i < 7; i++) {

		if (i == 6) {

			for (int j = 0; j < 5; j++) {

				ending.PushBack({ 1280 * (0 + j), 720 * (0 + i), 1280, 720 });

			}

		}
		else {

			for (int j = 0; j < 6; j++) {

				ending.PushBack({ 1280 * (0 + j), 720 * (0 + i), 1280, 720 });

			}

		}

	}
	ending.loop = true;
	ending.speed = 0.5f;


	return true;
}

// Called before the first frame
bool SceneEnding::Start()
{
	endingScreen = app->tex->Load("Assets/Textures/EndingScreen.png");

	currentAnimation = &ending;

	return true;
}

// Called each loop iteration
bool SceneEnding::PreUpdate()
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
bool SceneEnding::Update(float dt)
{
	OPTICK_EVENT();

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) {

		enableMusic = true;
		//app->fadeToBlack->Fade(this, (Module*)app->sceneTitle);
		app->fadeToBlack->Fade(this, reinterpret_cast<Module*>(app->sceneTitle));
	}

	currentAnimation->Update();

	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	app->render->DrawTexture(endingScreen,0,0, &rect);

	return true;
}

// Called each loop iteration
bool SceneEnding::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_BACK] == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool SceneEnding::CleanUp()
{

	return true;
}

bool SceneEnding::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}