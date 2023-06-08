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

#include "SceneLogo.h"
#include <memory>

SceneLogo::SceneLogo(bool startEnabled) : Module(startEnabled)
{
	nexusStudiosLogo = nullptr;
	nexusSpritesheet = nullptr;
	currentAnimation = nullptr;

	logoFX = NULL;

	enableMusic = true;
	FX_played = false;
	
	name.Create("sceneLogo");
	
}

// Destructor
SceneLogo::~SceneLogo()
{}

bool SceneLogo::Awake(pugi::xml_node& config)
{
	
	return true;
}

// Called before the first frame
bool SceneLogo::Start()
{
	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 3; j++) {

			nexus.PushBack({ 1280 * j, 720 * i, 1280, 720 });

		}
	}
	nexus.loop = true;
	nexus.speed = 0.5f;

	nexusSpritesheet = app->tex->Load("Assets/Textures/Intro_Animations/NexusAnimation.png");

	nexusStudiosLogo = app->tex->Load("Assets/Textures/SceneLogo.png");

	logoFX = app->audio->LoadFx("Assets/Audio/Fx/LogoFX2.wav");

	currentAnimation = &nexus;

	return true;
}

// Called each loop iteration
bool SceneLogo::PreUpdate()
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
bool SceneLogo::Update(float dt)
{
	OPTICK_EVENT();
	
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_A] == KEY_DOWN) {

		enableMusic = true;
		//app->fadeToBlack->Fade(this, (Module*)app->sceneTitle);
		app->fadeToBlack->Fade(this, reinterpret_cast<Module*>(app->sceneTitle));
		this->CleanUp();

	}

	app->render->DrawTexture(nexusStudiosLogo, 0, 0);

	if (!FX_played) {

		app->audio->PlayFx(logoFX);
		FX_played = true;

	}

	currentAnimation->Update();

	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	app->render->DrawTexture(nexusSpritesheet, 0, 0, &rect);

	return true;
}

// Called each loop iteration
bool SceneLogo::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;

	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_BACK] == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool SceneLogo::CleanUp()
{
	app->tex->UnLoad(nexusSpritesheet);
	app->tex->UnLoad(nexusStudiosLogo);

	return true;
}

bool SceneLogo::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}