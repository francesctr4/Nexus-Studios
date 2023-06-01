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
#include "SceneGameplay.h"
#include "Pause.h"

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

	for (int i = 0; i < 6; i++) {

		for (int j = 0; j < 4; j++) {

			title.PushBack({ 532 * j, 224 * i, 532, 224 });

		}
	}
	title.loop = true;
	title.speed = 0.4f;

	return true;
}

// Called before the first frame
bool SceneTitle::Start()
{
	//app->map->actualmap = 1;

	titleSpritesheet = app->tex->Load("Assets/Textures/Intro_Animations/Title_SpriteSheet.png");

	titleScreen = app->tex->Load("Assets/Textures/TitleScreen2.png");
	draggedOffTime = app->tex->Load("Assets/Textures/DraggedOffTime3.png");
	Fondo = app->tex->Load("Assets/UI/PauseBackground.png");

	enableMusic = true;

	titleFX = app->audio->LoadFx("Assets/Audio/Fx/TitleFX.wav");

	FX_played = false;

	// UI

	SettingsTitle = app->tex->Load("Assets/UI/SettingsTitle.png");


	newGame = app->tex->Load("Assets/UI/NewGame.png");
	NewGame = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 0, newGame, "", { 142,295,294,49 }, this);

	continue_ = app->tex->Load("Assets/UI/Continue.png");
	Continue_ = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 2, continue_, "", { 148,364,277,49 }, this);
	Continue_->state = GuiControlState::DISABLED;

	settings = app->tex->Load("Assets/UI/Settings.png");
	Settings = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, settings, "", { 148,433,277,55 }, this);

	credits = app->tex->Load("Assets/UI/Credits.png");
	Credits = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 4, credits, "", { 165,502,241,49 }, this);

	exit = app->tex->Load("Assets/UI/Exit.png");
	Exit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, exit, "", { 217,571,133,49 }, this);

	back = app->tex->Load("Assets/UI/Back.png");
	Back = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, back, "", { 586,592,102,38 }, this);
	Back->state = GuiControlState::DISABLED;

	slider = app->tex->Load("Assets/UI/Slider.png");
	SlideBar = app->tex->Load("Assets/UI/SlideBar.png");

	SliderMusic = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 7, slider, "", { 692,417,30,59 }, this);
	SliderMusic->state = GuiControlState::DISABLED;

	Music = app->tex->Load("Assets/UI/Music.png");

	SliderFX = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 8, slider, "", { 692,494,30,59 }, this);
	SliderFX->state = GuiControlState::DISABLED;

	SFX = app->tex->Load("Assets/UI/SFX.png");

	//Implementar control de los FPS

	framecap = app->tex->Load("Assets/UI/Framecap.png");
	FPS = app->tex->Load("Assets/UI/60FPS.png");

	framecapUP = app->tex->Load("Assets/UI/FramecapUP.png");
	FramecapUP = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 11, framecapUP, "", { 787,352,25,26 }, this);
	FramecapUP->state = GuiControlState::DISABLED;

	framecapDOWN = app->tex->Load("Assets/UI/FramecapDOWN.png");
	FramecapDOWN = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 11, framecapDOWN, "", { 787,374,25,26 }, this);
	FramecapDOWN->state = GuiControlState::DISABLED;


	checkBox = app->tex->Load("Assets/UI/CheckBox.png");

	CheckBoxFullscreen = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 9, checkBox, "", { 729,195,48,47 }, this);
	CheckBoxFullscreen->state = GuiControlState::DISABLED;

	checkBoxFullscreen = app->tex->Load("Assets/UI/Fullscreen.png");

	CheckBoxVsync = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 10, checkBox, "", { 729,270,48,47 }, this);
	CheckBoxVsync->state = GuiControlState::DISABLED;

	checkBoxVsync = app->tex->Load("Assets/UI/Vsync.png");

	BackCredits = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, back, "", { 1135,650,102,38 }, this);
	BackCredits->state = GuiControlState::DISABLED;

	showSettings = false;
	showCredits = false;
	continueEnabled = false;

	currentAnimation = &title;

	// Credits

	bigCredits = app->tex->Load("Assets/UI/Credits/BigCredits.png");

	people1 = app->tex->Load("Assets/UI/Credits/People1.png");
	people2 = app->tex->Load("Assets/UI/Credits/People2.png");

	// Tweens

	Animation_DraggedOffTime.Set();
	Animation_DraggedOffTime.smoothness = 4;
	Animation_DraggedOffTime.AddTween(100, 50, EXPONENTIAL_OUT);

	Animation_NewGame.Set();
	Animation_NewGame.smoothness = 4;
	Animation_NewGame.AddTween(100, 50, EXPONENTIAL_IN);
	Animation_NewGame.JumpTo(100, false);

	Animation_Continue.Set();
	Animation_Continue.smoothness = 4;
	Animation_Continue.AddTween(100, 50, EXPONENTIAL_IN);
	Animation_Continue.JumpTo(100, false);

	Animation_Settings.Set();
	Animation_Settings.smoothness = 4;
	Animation_Settings.AddTween(100, 50, EXPONENTIAL_IN);
	Animation_Settings.JumpTo(100, false);

	Animation_Credits.Set();
	Animation_Credits.smoothness = 4;
	Animation_Credits.AddTween(100, 50, EXPONENTIAL_IN);
	Animation_Credits.JumpTo(100, false);

	Animation_Exit.Set();
	Animation_Exit.smoothness = 4;
	Animation_Exit.AddTween(100, 50, EXPONENTIAL_IN);
	Animation_Exit.JumpTo(100, false);

	Animation_BigSettings.Set();
	Animation_BigSettings.smoothness = 4;
	Animation_BigSettings.AddTween(100, 50, EXPONENTIAL_OUT);

	Animation_Back.Set();
	Animation_Back.smoothness = 4;
	Animation_Back.AddTween(100, 50, EXPONENTIAL_IN);

	// Tweens Credits

	Animation_BigCredits.Set();
	Animation_BigCredits.smoothness = 4;
	Animation_BigCredits.AddTween(100, 50, EXPONENTIAL_OUT);

	Animation_People1.Set();
	Animation_People1.smoothness = 4;
	Animation_People1.AddTween(100, 50, EXPONENTIAL_OUT);

	Animation_People2.Set();
	Animation_People2.smoothness = 4;
	Animation_People2.AddTween(100, 50, EXPONENTIAL_IN);

	Animation_BackCredits.Set();
	Animation_BackCredits.smoothness = 4;
	Animation_BackCredits.AddTween(100, 50, EXPONENTIAL_IN);

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

	if (!FX_played) {

		app->audio->PlayFx(titleFX);
		FX_played = true;

	}

	// Tweens

	Animation_DraggedOffTime.Step(1, false);
	Animation_NewGame.Step(1, false);
	Animation_Continue.Step(1, false);
	Animation_Settings.Step(1, false);
	Animation_Credits.Step(1, false);
	Animation_Exit.Step(1, false);

	Animation_BigSettings.Step(1, false);
	Animation_Back.Step(1, false);

	Animation_BigCredits.Step(1, false);
	Animation_People1.Step(1, false);
	Animation_People2.Step(1, false);
	Animation_BackCredits.Step(1, false);

	Animation_DraggedOffTime.Foward();
	Animation_NewGame.Backward();
	Animation_Continue.Backward();
	Animation_Settings.Backward();
	Animation_Credits.Backward();
	Animation_Exit.Backward();

	if (showSettings) {

		Animation_BigSettings.Foward();
		Animation_Back.Backward();

	}
	else {

		Animation_BigSettings.JumpTo(0, false);
		Animation_Back.JumpTo(100, false);

	}

	if (showCredits) {

		Animation_BigCredits.Foward();
		Animation_People1.Foward();
		Animation_People2.Backward();
		Animation_BackCredits.Backward();

	}
	else {

		Animation_BigCredits.JumpTo(0, false);
		Animation_People1.JumpTo(0, false);
		Animation_People2.JumpTo(100, false);
		Animation_BackCredits.JumpTo(100, false);

	}

	point_DraggedOffTime = Animation_DraggedOffTime.GetPoint();
	point_NewGame = Animation_NewGame.GetPoint();
	point_Continue = Animation_Continue.GetPoint();
	point_Settings = Animation_Settings.GetPoint();
	point_Credits = Animation_Credits.GetPoint();
	point_Exit = Animation_Exit.GetPoint();

	point_BigSettings = Animation_BigSettings.GetPoint();
	point_Back = Animation_Back.GetPoint();

	point_BigCredits = Animation_BigCredits.GetPoint();
	point_People1 = Animation_People1.GetPoint();
	point_People2 = Animation_People2.GetPoint();
	point_BackCredits = Animation_BackCredits.GetPoint();

	NewGame->bounds.x = point_NewGame * offset + 143;
	Continue_->bounds.x = point_Continue * offset + 149;
	Settings->bounds.x = point_Settings * offset + 149;
	Credits->bounds.x = point_Credits * offset + 164;
	Exit->bounds.x = point_Exit * offset + 214;

	Back->bounds.y = point_Back * offset + 594;

	BackCredits->bounds.y = point_BackCredits * offset + 655;

	// UI

	if (NewGame->state == GuiControlState::PRESSED || app->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) {

		enableMusic = true;
		NewGame->state = GuiControlState::DISABLED;
		Continue_->state = GuiControlState::DISABLED;
		Settings->state = GuiControlState::DISABLED;
		Credits->state = GuiControlState::DISABLED;
		Exit->state = GuiControlState::DISABLED;

		Animation_DraggedOffTime.JumpTo(0, false);
		Animation_NewGame.JumpTo(100, false);
		Animation_Continue.JumpTo(100, false);
		Animation_Settings.JumpTo(100, false);
		Animation_Credits.JumpTo(100, false);
		Animation_Exit.JumpTo(100, false);

		app->fadeToBlack->Fade(this, (Module*)app->sceneGameplay);

		app->sceneGameplay->player->pbody->body->SetTransform({ PIXEL_TO_METERS(150),PIXEL_TO_METERS(430) }, 0);

	}

	if (Continue_->state == GuiControlState::PRESSED) {

		enableMusic = true;

		NewGame->state = GuiControlState::DISABLED;
		Continue_->state = GuiControlState::DISABLED;
		Settings->state = GuiControlState::DISABLED;
		Credits->state = GuiControlState::DISABLED;
		Exit->state = GuiControlState::DISABLED;

		Animation_DraggedOffTime.JumpTo(0, false);
		Animation_NewGame.JumpTo(100, false);
		Animation_Continue.JumpTo(100, false);
		Animation_Settings.JumpTo(100, false);
		Animation_Credits.JumpTo(100, false);
		Animation_Exit.JumpTo(100, false);

		app->fadeToBlack->Fade(this, (Module*)app->sceneGameplay);

	}

	if (Settings->state == GuiControlState::PRESSED) {

		showSettings = true;
		Back->state = GuiControlState::NORMAL;

	}

	if (Back->state == GuiControlState::PRESSED) {
		showSettings = false;
	}

	if (Credits->state == GuiControlState::PRESSED) {

		showCredits = true;
		BackCredits->state = GuiControlState::NORMAL;

	}

	if (BackCredits->state == GuiControlState::PRESSED) {

		showCredits = false;

	}

	if (CheckBoxFullscreen->crossed) {

		app->sceneGameplay->pause.CheckBoxFullscreen->crossed = true;
		SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_RenderSetLogicalSize(app->render->renderer, 1280, 720);

	}

	if (!CheckBoxFullscreen->crossed) {

		app->sceneGameplay->pause.CheckBoxFullscreen->crossed = false;
		SDL_SetWindowFullscreen(app->win->window, 0);

	}

	if (CheckBoxVsync->crossed) {

		app->sceneGameplay->pause.CheckBoxVsync->crossed = true;
		SDL_GL_SetSwapInterval(1);

	}

	if (!CheckBoxVsync->crossed) {

		app->sceneGameplay->pause.CheckBoxVsync->crossed = false;
		SDL_GL_SetSwapInterval(0);

	}

	app->sceneGameplay->pause.SliderMusic->bounds.x = SliderMusic->bounds.x;
	app->sceneGameplay->pause.SliderMusic->posx = SliderMusic->posx;

	app->sceneGameplay->pause.SliderFX->bounds.x = SliderFX->bounds.x;
	app->sceneGameplay->pause.SliderFX->posx = SliderFX->posx;

	Mix_VolumeMusic((SliderMusic->bounds.x - 631) * (128 - 0) / (753 - 631) + 0);

	for (int i = 0; i < app->audio->fx.Count(); i++) {

		Mix_VolumeChunk(app->audio->fx.At(i)->data, (SliderFX->bounds.x - 631) * (128 - 0) / (753 - 631) + 0);

	}

	//app->scene->startCounting = true;

	currentAnimation->Update();

	return true;
}

// Called each loop iteration
bool SceneTitle::PostUpdate()
{
	OPTICK_EVENT();

	bool ret = true;

	app->render->DrawTexture(titleScreen, 0, 0);

	app->guiManager->Draw();

	SDL_Rect rect = currentAnimation->GetCurrentFrame();

	if (!showSettings && !showCredits) {

		//app->render->DrawTexture(titleSpritesheet, 30, 45, &rect);
		app->render->DrawTexture(titleSpritesheet, 30, point_DraggedOffTime * offset - 758, &rect);

	}
	
	if (showCredits && !showSettings) {

		app->render->DrawTexture(Fondo, 0, 0);

		//app->render->DrawTexture(bigCredits, 476, 43);
		app->render->DrawTexture(bigCredits, 476, point_BigCredits * offset - 760);

		//app->render->DrawTexture(people1, 230, 152);
		app->render->DrawTexture(people1, point_People1 * offset - 576, 152);

		//app->render->DrawTexture(people2, 701, 152);
		app->render->DrawTexture(people2, point_People2 * offset + 700, 152);

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

	if (showSettings && !showCredits) {

		app->render->DrawTexture(Fondo, 0, 0);

		app->render->DrawTexture(SlideBar, 636, 438);
		app->render->DrawTexture(SlideBar, 636, 515);

		if (Back->state == GuiControlState::DISABLED) Back->state = GuiControlState::NORMAL;
		if (SliderMusic->state == GuiControlState::DISABLED) SliderMusic->state = GuiControlState::NORMAL;
		if (SliderFX->state == GuiControlState::DISABLED) SliderFX->state = GuiControlState::NORMAL;
		if (CheckBoxFullscreen->state == GuiControlState::DISABLED) CheckBoxFullscreen->state = GuiControlState::NORMAL;
		if (CheckBoxVsync->state == GuiControlState::DISABLED) CheckBoxVsync->state = GuiControlState::NORMAL;
		if (FramecapUP->state == GuiControlState::DISABLED) FramecapUP->state = GuiControlState::NORMAL;
		if (FramecapDOWN->state == GuiControlState::DISABLED) FramecapDOWN->state = GuiControlState::NORMAL;

		if (NewGame->state != GuiControlState::DISABLED) NewGame->state = GuiControlState::DISABLED;
		if (Continue_->state != GuiControlState::DISABLED) Continue_->state = GuiControlState::DISABLED;
		if (Settings->state != GuiControlState::DISABLED) Settings->state = GuiControlState::DISABLED;
		if (Credits->state != GuiControlState::DISABLED) Credits->state = GuiControlState::DISABLED;
		if (Exit->state != GuiControlState::DISABLED) Exit->state = GuiControlState::DISABLED;

		//app->render->DrawTexture(SettingsTitle, 449, 73);
		app->render->DrawTexture(SettingsTitle, 449, point_BigSettings * offset - 734);

		app->render->DrawTexture(checkBoxFullscreen, 496, 202);
		app->render->DrawTexture(checkBoxVsync, 496, 279);
		app->render->DrawTexture(framecap, 496, 356);
		app->render->DrawTexture(FPS, 728, 364);
		app->render->DrawTexture(Music, 496, 433);
		app->render->DrawTexture(SFX, 496, 510);

		Back->Draw(app->render);
		SliderMusic->Draw(app->render);
		SliderFX->Draw(app->render);
		CheckBoxFullscreen->Draw(app->render);
		CheckBoxVsync->Draw(app->render);
		FramecapUP->Draw(app->render);
		FramecapUP->Draw(app->render);
		FramecapDOWN->Draw(app->render);



		/*if (app->win->configWindow.child("fullscreen").attribute("value").as_bool() == false) {
			app->win->configWindow.child("fullscreen").append_attribute("value") = "true";
		}*/

	}

	if (!showSettings && !showCredits) {

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
		if (FramecapUP->state != GuiControlState::DISABLED) FramecapUP->state = GuiControlState::DISABLED;
		if (FramecapDOWN->state != GuiControlState::DISABLED) FramecapDOWN->state = GuiControlState::DISABLED;

	}

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