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

SceneLogo::SceneLogo(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneLogo");
	
}

// Destructor
SceneLogo::~SceneLogo()
{}

bool SceneLogo::Awake(pugi::xml_node& config)
{

	for (int i = 0; i < 17; i++) {

		for (int j = 0; j < 8; j++) {

			nexus1.PushBack({ 1280 * j, 720 * i, 1280, 720 });

		}
	}
	nexus1.loop = true;
	nexus1.speed = 0.5f;

	for (int i = 0; i < 4; i++) {

		for (int j = 0; j < 3; j++) {

			nexus2.PushBack({ 1280 * j, 720 * i, 1280, 720 });

		}
	}
	nexus2.loop = true;
	nexus2.speed = 0.5f;

	return true;
}

// Called before the first frame
bool SceneLogo::Start()
{
	//app->map->actualmap = 0;

	//bool retLoad = app->map->Load();

	//nexusSpritesheet1 = app->tex->Load("Assets/Textures/Intro_Animations/NexusAnimation1.png");
	nexusSpritesheet2 = app->tex->Load("Assets/Textures/Intro_Animations/NexusAnimation2.png");

	nexusStudiosLogo = app->tex->Load("Assets/Textures/SceneLogo.png");

	logoFX = app->audio->LoadFx("Assets/Audio/Fx/LogoFX2.wav");

	enableMusic = true;

	FX_played = false;

	currentAnimation = &nexus2;

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
	
	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) {

		enableMusic = true;
		app->fadeToBlack->Fade(this, (Module*)app->sceneTitle);
		this->CleanUp();

	}

	app->render->DrawTexture(nexusStudiosLogo, 0, 0);

	if (!FX_played) {

		app->audio->PlayFx(logoFX);
		FX_played = true;

	}

	currentAnimation->Update();

	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	app->render->DrawTexture(nexusSpritesheet2, 0, 0, &rect);

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
	LOG("Freeing scene");

	app->tex->UnLoad(nexusSpritesheet2);
	app->tex->UnLoad(nexusStudiosLogo);

	return true;
}

bool SceneLogo::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}