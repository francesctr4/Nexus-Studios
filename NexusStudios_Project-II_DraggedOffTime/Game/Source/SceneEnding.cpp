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

	enteredEnding = false;

}

// Destructor
SceneEnding::~SceneEnding()
{}

bool SceneEnding::Awake(pugi::xml_node& config)
{

	return true;
}

// Called before the first frame
bool SceneEnding::Start()
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

	endingScreen = app->tex->Load("Assets/Textures/EndingScreen.png");

	currentAnimation = &ending;

	// UI

	resume = app->tex->Load("Assets/UI/Resume.png");
	Resume = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 0, resume, "", { 170,481,154,38 }, (Module*)app->sceneGameplay);
	Resume->state = GuiControlState::DISABLED;

	Animation_Resume.Set();
	Animation_Resume.smoothness = 4;
	Animation_Resume.AddTween(100, 50, EXPONENTIAL_OUT);

	backTitle = app->tex->Load("Assets/UI/BackTitle.png");
	BackTitle = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 1, backTitle, "", { 872,481,270,38 }, (Module*)app->sceneGameplay);
	BackTitle->state = GuiControlState::DISABLED;

	Animation_BackTitle.Set();
	Animation_BackTitle.smoothness = 4;
	Animation_BackTitle.AddTween(100, 50, EXPONENTIAL_IN);
	Animation_BackTitle.JumpTo(100, false);


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

	if (!enteredEnding) {

		Resume->state = GuiControlState::NORMAL;
		BackTitle->state = GuiControlState::NORMAL;

		enteredEnding = true;

	}

	Animation_Resume.Step(1, false);
	Animation_BackTitle.Step(1, false);

	Animation_Resume.Foward();
	Animation_BackTitle.Backward();

	point_Resume = Animation_Resume.GetPoint();
	point_BackTitle = Animation_BackTitle.GetPoint();

	Resume->bounds.x = point_Resume * offset - 615;
	BackTitle->bounds.x = point_BackTitle * offset + 865;

	if (Resume->state == GuiControlState::PRESSED) {

		app->sceneGameplay->enableMusic = true;

		Resume->state = GuiControlState::DISABLED;
		BackTitle->state = GuiControlState::DISABLED;
		enteredEnding = false;

		enableMusic = true;

		Animation_Resume.JumpTo(0, false);
		Animation_BackTitle.JumpTo(100, false);

		app->fadeToBlack->Fade(this, reinterpret_cast<Module*>(app->sceneGameplay));

	}

	if (BackTitle->state == GuiControlState::PRESSED) {

		app->sceneGameplay->enableMusic = true;

		Resume->state = GuiControlState::DISABLED;
		BackTitle->state = GuiControlState::DISABLED;
		enteredEnding = false;

		enableMusic = true;

		Animation_Resume.JumpTo(0, false);
		Animation_BackTitle.JumpTo(100, false);

		app->sceneGameplay->LoadMap(1);
		app->sceneGameplay->player->Teleport(640, 570);

		app->fadeToBlack->Fade(this, reinterpret_cast<Module*>(app->sceneTitle));

	}

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

	app->guiManager->Draw();

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