#include "Pause.h"
#include "Textures.h"
#include "App.h"
#include "Render.h"
#include "Audio.h"
#include "Window.h"
#include "SceneTitle.h"
#include "SceneGameplay.h"
#include "FadeToBlack.h"

#include "SDL_mixer/include/SDL_mixer.h"

void Pause::Load()
{
	Fondo = app->tex->Load("Assets/UI/PauseBackground.png");

	//Pause UI

	PauseTitle = app->tex->Load("Assets/UI/PauseTitle.png");

	resume = app->tex->Load("Assets/UI/Resume.png");
	Resume = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, resume, "", { 560,267,154,38 }, (Module*)app->sceneGameplay);
	Resume->state = GuiControlState::DISABLED;

	settings = app->tex->Load("Assets/UI/PauseSettings.png");
	Settings = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, settings, "", { 544,374,186,42 }, (Module*)app->sceneGameplay);
	Settings->state = GuiControlState::DISABLED;

	backTitle = app->tex->Load("Assets/UI/BackTitle.png");
	BackTitle = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 3, backTitle, "", { 502,481,270,38 }, (Module*)app->sceneGameplay);
	BackTitle->state = GuiControlState::DISABLED;

	exit = app->tex->Load("Assets/UI/PauseExit.png");
	Exit = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 5, exit, "", { 592,588,90,38 }, (Module*)app->sceneGameplay);
	Exit->state = GuiControlState::DISABLED;

	//Settings UI

	showSettings = false;

	SettingsTitle = app->tex->Load("Assets/UI/SettingsTitle.png");

	checkBox = app->tex->Load("Assets/UI/CheckBox.png");

	checkBoxFullscreen = app->tex->Load("Assets/UI/Fullscreen.png");
	CheckBoxFullscreen = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 9, checkBox, "", { 729,195,48,47 }, (Module*)app->sceneGameplay);
	CheckBoxFullscreen->state = GuiControlState::DISABLED;

	checkBoxVsync = app->tex->Load("Assets/UI/Vsync.png");
	CheckBoxVsync = (GuiCheckBox*)app->guiManager->CreateGuiControl(GuiControlType::CHECKBOX, 10, checkBox, "", { 729,270,48,47 }, (Module*)app->sceneGameplay);
	CheckBoxVsync->state = GuiControlState::DISABLED;


	framecap = app->tex->Load("Assets/UI/Framecap.png");
	FPS = app->tex->Load("Assets/UI/60FPS.png");

	framecapUP = app->tex->Load("Assets/UI/FramecapUP.png");
	FramecapUP = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 11, framecapUP, "", { 787,352,25,26 }, (Module*)app->sceneGameplay);
	FramecapUP->state = GuiControlState::DISABLED;

	framecapDOWN = app->tex->Load("Assets/UI/FramecapDOWN.png");
	FramecapDOWN = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 11, framecapDOWN, "", { 787,374,25,26 }, (Module*)app->sceneGameplay);
	FramecapDOWN->state = GuiControlState::DISABLED;


	slider = app->tex->Load("Assets/UI/Slider.png");
	SlideBar = app->tex->Load("Assets/UI/SlideBar.png");

	Music = app->tex->Load("Assets/UI/Music.png");
	SliderMusic = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 7, slider, "", { 692,417,30,59 }, (Module*)app->sceneGameplay);
	SliderMusic->state = GuiControlState::DISABLED;

	SFX = app->tex->Load("Assets/UI/SFX.png");
	SliderFX = (GuiSlider*)app->guiManager->CreateGuiControl(GuiControlType::SLIDER, 8, slider, "", { 692,494,30,59 }, (Module*)app->sceneGameplay);
	SliderFX->state = GuiControlState::DISABLED;


	back = app->tex->Load("Assets/UI/Back.png");
	Back = (GuiButton*)app->guiManager->CreateGuiControl(GuiControlType::BUTTON, 6, back, "", { 586,622,102,38 }, (Module*)app->sceneGameplay);
	Back->state = GuiControlState::DISABLED;

	OpenPause = app->audio->LoadFx("Assets/Audio/Fx/OpenPause.wav");
	ClosePause = app->audio->LoadFx("Assets/Audio/Fx/ClosePause.wav");
}

void Pause::Update()
{
	//UI
	if (app->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN || app->input->controllers[0].buttons[SDL_CONTROLLER_BUTTON_START] == KEY_DOWN) {

		showPause = true;
	}

	if (Resume->state == GuiControlState::PRESSED) {

		showPause = false;
		app->audio->PlayFx(OpenPause);
	}

	if (Settings->state == GuiControlState::PRESSED) {

		showSettings = true;
		app->audio->PlayFx(OpenPause);
		Back->state = GuiControlState::NORMAL;

	}

	if (BackTitle->state == GuiControlState::PRESSED) {

		app->sceneGameplay->enableMusic = true;
		Resume->state = GuiControlState::DISABLED;
		Settings->state = GuiControlState::DISABLED;
		BackTitle->state = GuiControlState::DISABLED;
		Exit->state = GuiControlState::DISABLED;
		showPause = false;

		app->fadeToBlack->Fade((Module*)app->sceneGameplay, (Module*)app->sceneTitle);

	}

	if (CheckBoxFullscreen->crossed) {

		app->sceneTitle->CheckBoxFullscreen->crossed = true;
		SDL_SetWindowFullscreen(app->win->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
		SDL_RenderSetLogicalSize(app->render->renderer, 1280, 720);

	}

	if (!CheckBoxFullscreen->crossed) {

		app->sceneTitle->CheckBoxFullscreen->crossed = false;
		SDL_SetWindowFullscreen(app->win->window, 0);

	}

	if (CheckBoxVsync->crossed) {

		app->sceneTitle->CheckBoxVsync->crossed = true;
		SDL_GL_SetSwapInterval(1);

	}
	if (!CheckBoxVsync->crossed) {

		app->sceneTitle->CheckBoxVsync->crossed = false;
		SDL_GL_SetSwapInterval(0);

	}

	app->sceneTitle->SliderMusic->bounds.x = SliderMusic->bounds.x;
	app->sceneTitle->SliderMusic->posx = SliderMusic->posx;

	app->sceneTitle->SliderFX->bounds.x = SliderFX->bounds.x;
	app->sceneTitle->SliderFX->posx = SliderFX->posx;

	Mix_VolumeMusic((SliderMusic->bounds.x - 631) * (128 - 0) / (753 - 631) + 0);

	for (int i = 0; i < app->audio->fx.Count(); i++) {

		Mix_VolumeChunk(app->audio->fx.At(i)->data, (SliderFX->bounds.x - 631) * (128 - 0) / (753 - 631) + 0);

	}

	if (Back->state == GuiControlState::PRESSED) {
		showSettings = false;
		showPause = true;
		app->audio->PlayFx(ClosePause);
	}
}

void Pause::PostUpdate()
{
	app->guiManager->Draw();

	//Pause UI

	if (showPause || showSettings) app->render->DrawTexture(Fondo, 0, 0);

	if (showPause) {

		if (Resume->state == GuiControlState::DISABLED) Resume->state = GuiControlState::NORMAL;
		if (Settings->state == GuiControlState::DISABLED) Settings->state = GuiControlState::NORMAL;
		if (BackTitle->state == GuiControlState::DISABLED) BackTitle->state = GuiControlState::NORMAL;
		if (Exit->state == GuiControlState::DISABLED) Exit->state = GuiControlState::NORMAL;

		app->render->DrawTexture(PauseTitle, 512, 143);

		Resume->Draw(app->render);
		Settings->Draw(app->render);
		BackTitle->Draw(app->render);
		Exit->Draw(app->render);

	}
	if (!showPause) {

		if (Resume->state != GuiControlState::DISABLED) Resume->state = GuiControlState::DISABLED;
		if (Settings->state != GuiControlState::DISABLED) Settings->state = GuiControlState::DISABLED;
		if (BackTitle->state != GuiControlState::DISABLED) BackTitle->state = GuiControlState::DISABLED;
		if (Exit->state != GuiControlState::DISABLED) Exit->state = GuiControlState::DISABLED;

	}

	//Settings UI

	if (showSettings) {

		showPause = false;

		app->render->DrawTexture(SlideBar, 636, 438);
		app->render->DrawTexture(SlideBar, 636, 515);

		if (Back->state == GuiControlState::DISABLED) Back->state = GuiControlState::NORMAL;
		if (SliderMusic->state == GuiControlState::DISABLED) SliderMusic->state = GuiControlState::NORMAL;
		if (SliderFX->state == GuiControlState::DISABLED) SliderFX->state = GuiControlState::NORMAL;
		if (CheckBoxFullscreen->state == GuiControlState::DISABLED) CheckBoxFullscreen->state = GuiControlState::NORMAL;
		if (CheckBoxVsync->state == GuiControlState::DISABLED) CheckBoxVsync->state = GuiControlState::NORMAL;
		if (FramecapUP->state == GuiControlState::DISABLED) FramecapUP->state = GuiControlState::NORMAL;
		if (FramecapDOWN->state == GuiControlState::DISABLED) FramecapDOWN->state = GuiControlState::NORMAL;


		app->render->DrawTexture(SettingsTitle, 449, 73);
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

	if (!showSettings) {

		if (Back->state != GuiControlState::DISABLED) Back->state = GuiControlState::DISABLED;
		if (SliderMusic->state != GuiControlState::DISABLED) SliderMusic->state = GuiControlState::DISABLED;
		if (SliderFX->state != GuiControlState::DISABLED) SliderFX->state = GuiControlState::DISABLED;
		if (CheckBoxFullscreen->state != GuiControlState::DISABLED) CheckBoxFullscreen->state = GuiControlState::DISABLED;
		if (CheckBoxVsync->state != GuiControlState::DISABLED) CheckBoxVsync->state = GuiControlState::DISABLED;
		if (FramecapUP->state != GuiControlState::DISABLED) FramecapUP->state = GuiControlState::DISABLED;
		if (FramecapDOWN->state != GuiControlState::DISABLED) FramecapDOWN->state = GuiControlState::DISABLED;

	}

}