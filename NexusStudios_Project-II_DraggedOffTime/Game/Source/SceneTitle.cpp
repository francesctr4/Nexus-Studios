#include "App.h"
#include "Defs.h"
#include "Log.h"

#include "Input.h"
#include "Textures.h"
#include "Audio.h"
#include "Render.h"
#include "Window.h"
#include "Physics.h"
#include "FadeToBlack.h"
#include "EntityManager.h"
#include "Map.h"

#include "SceneTitle.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer/include/SDL_mixer.h"

SceneTitle::SceneTitle(bool startEnabled) : Module(startEnabled)
{
	name.Create("sceneTitle");
}

// Destructor
SceneTitle::~SceneTitle()
{}

bool SceneTitle::Awake(pugi::xml_node& config)
{

	return true;
}

// Called before the first frame
bool SceneTitle::Start()
{
	//app->map->actualmap = 1;

	titleScreen = app->tex->Load("Assets/Textures/TitleScreen2.png");
	draggedOffTime = app->tex->Load("Assets/Textures/DraggedOffTime3.png");

	enableMusic = true;

	titleFX = app->audio->LoadFx("Assets/Audio/Fx/TitleFX.wav");

	FX_played = false;

	// UI

	newGame = app->tex->Load("Assets/UI/NewGame.png"); 

	NewGame = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 0, newGame, "", { 142,295,294,49 }, this);

	continue_ = app->tex->Load("Assets/UI/Continue.png");
	Continue_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, continue_, "", { 148,364,277,49 }, this);
	Continue_->state = GuiControlState::DISABLED;

	settings = app->tex->Load("Assets/UI/Settings.png");

	Settings = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, settings, "", { 148,433,277,49 }, this);

	credits = app->tex->Load("Assets/UI/Credits.png");

	Credits = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, credits, "", { 165,502,241,49 }, this);

	exit = app->tex->Load("Assets/UI/Exit.png");

	Exit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, exit, "", { 217,571,133,49 }, this);

	back = app->tex->Load("Assets/UI/Back.png");
	Back = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, back, "", { 704,619,112,59 }, this);
	Back->state = GuiControlState::DISABLED;

	slider = app->tex->Load("Assets/UI/Slider.png");

	SliderMusic = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 7, slider, "", { 621,220,30,59 }, this);
	SliderMusic->state = GuiControlState::DISABLED;

	SliderFX = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 8, slider, "", { 621,375,30,59 }, this);
	SliderFX->state = GuiControlState::DISABLED;

	checkBox = app->tex->Load("Assets/UI/CheckBox.png");

	CheckBoxFullscreen = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 9, checkBox, "", { 701,472,48,47 }, this);
	CheckBoxFullscreen->state = GuiControlState::DISABLED;

	CheckBoxVsync = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 10, checkBox, "", { 610,570,48,47 }, this);
	CheckBoxVsync->state = GuiControlState::DISABLED;

	BackCredits = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, back, "", { 704,619,112,59 }, this);
	BackCredits->state = GuiControlState::DISABLED;

	showSettings = false;
	showCredits = false;
	continueEnabled = false;

	OpenPause = app->audio->LoadFx("Assets/Audio/Fx/OpenPause.wav");
	ClosePause = app->audio->LoadFx("Assets/Audio/Fx/ClosePause.wav");

	return true;
}

// Called each loop iteration
bool SceneTitle::PreUpdate()
{
	OPTICK_EVENT();
	app->entityManager->Disable();

	if (enableMusic) {

		app->audio->PlayMusic("Assets/Audio/Music/MenuTheme.ogg", 0);
		enableMusic = false;

	}

	return true;
}

// Called each loop iteration
bool SceneTitle::Update(float dt)
{
	OPTICK_EVENT();

	if (app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) {
		
		enableMusic = true;
		app->fadeToBlack->Fade(this, (Module*)app->sceneGameplay);

	}

	app->render->DrawTexture(titleScreen, 0, 0);

	if (!FX_played) {

		app->audio->PlayFx(titleFX);
		FX_played = true;

	}

	//app->map->Draw();

	// UI

	if (NewGame->state == GuiControlState::PRESSED) {

		enableMusic = true;

		app->fadeToBlack->Fade(this, (Module*)app->sceneGameplay);

	}

	if (Continue_->state == GuiControlState::PRESSED) {

		enableMusic = true;

		app->fadeToBlack->Fade(this, (Module*)app->sceneGameplay);

	}

	if (Settings->state == GuiControlState::PRESSED) {

		showSettings = true;
		app->audio->PlayFx(OpenPause);
		Back->state = GuiControlState::NORMAL;

	}

	if (Back->state == GuiControlState::PRESSED) {
		showSettings = false;
		app->audio->PlayFx(ClosePause);
	}

	if (Credits->state == GuiControlState::PRESSED) {

		showCredits = true;
		app->audio->PlayFx(OpenPause);
		BackCredits->state = GuiControlState::NORMAL;

	}

	if (BackCredits->state == GuiControlState::PRESSED) {

		showCredits = false;
		app->audio->PlayFx(ClosePause);

	}

	if (CheckBoxFullscreen->crossed) {

		//app->scene->CheckBoxFullscreen->crossed = true;
		SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_RenderSetLogicalSize(app->render->renderer, 1280, 720);

	}

	if (!CheckBoxFullscreen->crossed) {

		//app->scene->CheckBoxFullscreen->crossed = false;
		SDL_SetWindowFullscreen(app->win->window, 0);

	}

	if (CheckBoxVsync->crossed) {

		//app->scene->CheckBoxVsync->crossed = true;
		SDL_GL_SetSwapInterval(1);

	}

	if (!CheckBoxVsync->crossed) {

		//app->scene->CheckBoxVsync->crossed = false;
		SDL_GL_SetSwapInterval(0);

	}

	//app->scene->SliderMusic->bounds.x = SliderMusic->bounds.x;
	//app->scene->SliderMusic->posx = SliderMusic->posx;

	//app->scene->SliderFX->bounds.x = SliderFX->bounds.x;
	//app->scene->SliderFX->posx = SliderFX->posx;

	Mix_VolumeMusic((SliderMusic->bounds.x - 324) * (128 - 0) / (674 - 324) + 0);

	for (int i = 0; i < app->audio->fx.Count(); i++) {

		Mix_VolumeChunk(app->audio->fx.At(i)->data, (SliderFX->bounds.x - 324) * (128 - 0) / (674 - 324) + 0);

	}

	//app->scene->startCounting = true;

	return true;
}

// Called each loop iteration
bool SceneTitle::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;

	app->guiManager->Draw();

	if (showCredits) {

		if (BackCredits->state == GuiControlState::DISABLED) BackCredits->state = GuiControlState::NORMAL;

		if (NewGame->state != GuiControlState::DISABLED) NewGame->state = GuiControlState::DISABLED;
		if (Continue_->state != GuiControlState::DISABLED) Continue_->state = GuiControlState::DISABLED;
		if (Settings->state != GuiControlState::DISABLED) Settings->state = GuiControlState::DISABLED;
		if (Credits->state != GuiControlState::DISABLED) Credits->state = GuiControlState::DISABLED;
		if (Exit->state != GuiControlState::DISABLED) Exit->state = GuiControlState::DISABLED;

		BackCredits->Draw(app->render);

	}

	if (!showCredits) {

		if (NewGame->state == GuiControlState::DISABLED) NewGame->state = GuiControlState::NORMAL;
		if (Continue_->state == GuiControlState::DISABLED && continueEnabled) Continue_->state = GuiControlState::NORMAL;
		if (Settings->state == GuiControlState::DISABLED) Settings->state = GuiControlState::NORMAL;
		if (Credits->state == GuiControlState::DISABLED) Credits->state = GuiControlState::NORMAL;
		if (Exit->state == GuiControlState::DISABLED) Exit->state = GuiControlState::NORMAL;

		if (BackCredits->state != GuiControlState::DISABLED) BackCredits->state = GuiControlState::DISABLED;

	}

	if (showSettings) {

		if (Back->state == GuiControlState::DISABLED) Back->state = GuiControlState::NORMAL;
		if (SliderMusic->state == GuiControlState::DISABLED) SliderMusic->state = GuiControlState::NORMAL;
		if (SliderFX->state == GuiControlState::DISABLED) SliderFX->state = GuiControlState::NORMAL;
		if (CheckBoxFullscreen->state == GuiControlState::DISABLED) CheckBoxFullscreen->state = GuiControlState::NORMAL;
		if (CheckBoxVsync->state == GuiControlState::DISABLED) CheckBoxVsync->state = GuiControlState::NORMAL;

		if (NewGame->state != GuiControlState::DISABLED) NewGame->state = GuiControlState::DISABLED;
		if (Continue_->state != GuiControlState::DISABLED) Continue_->state = GuiControlState::DISABLED;
		if (Settings->state != GuiControlState::DISABLED) Settings->state = GuiControlState::DISABLED;
		if (Credits->state != GuiControlState::DISABLED) Credits->state = GuiControlState::DISABLED;
		if (Exit->state != GuiControlState::DISABLED) Exit->state = GuiControlState::DISABLED;

		Back->Draw(app->render);
		SliderMusic->Draw(app->render);
		SliderFX->Draw(app->render);
		CheckBoxFullscreen->Draw(app->render);
		CheckBoxVsync->Draw(app->render);

		/*if (app->win->configWindow.child("fullscreen").attribute("value").as_bool() == false) {
			app->win->configWindow.child("fullscreen").append_attribute("value") = "true";
		}*/

	}

	if (!showSettings) {

		if (NewGame->state == GuiControlState::DISABLED) NewGame->state = GuiControlState::NORMAL;
		if (Continue_->state == GuiControlState::DISABLED && continueEnabled) Continue_->state = GuiControlState::NORMAL;
		if (Settings->state == GuiControlState::DISABLED) Settings->state = GuiControlState::NORMAL;
		if (Credits->state == GuiControlState::DISABLED) Credits->state = GuiControlState::NORMAL;
		if (Exit->state == GuiControlState::DISABLED) Exit->state = GuiControlState::NORMAL;

		if (Back->state != GuiControlState::DISABLED) Back->state = GuiControlState::DISABLED;
		if (SliderMusic->state != GuiControlState::DISABLED) SliderMusic->state = GuiControlState::DISABLED;
		if (SliderFX->state != GuiControlState::DISABLED) SliderFX->state = GuiControlState::DISABLED;
		if (CheckBoxFullscreen->state != GuiControlState::DISABLED) CheckBoxFullscreen->state = GuiControlState::DISABLED;
		if (CheckBoxVsync->state != GuiControlState::DISABLED) CheckBoxVsync->state = GuiControlState::DISABLED;

	}

	app->render->DrawTexture(draggedOffTime,-12,50);

	//app->scene->player->hitsTaken = 0;

	if (Exit->state == GuiControlState::PRESSED || app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_BACK] == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool SceneTitle::CleanUp()
{
	LOG("Freeing scene");

	//app->map->CleanUp();

	

	return true;
}

bool SceneTitle::OnGuiMouseClickEvent(GuiControl* control)
{

	return true;
}