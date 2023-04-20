#pragma once

#include "GuiManager.h"
#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"

struct SDL_Texture;

class SceneTitle : public Module
{
public:

	SceneTitle(bool startEnabled);

	// Destructor
	virtual ~SceneTitle();

	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool OnGuiMouseClickEvent(GuiControl* control);

public:

	bool enableMusic;

	uint titleFX;
	bool FX_played;

	bool showSettings;

private:


	SDL_Texture* Fondo;

	SDL_Texture* titleScreen;
	SDL_Texture* draggedOffTime;

	SDL_Texture* newGame;
	GuiButton* NewGame;

	SDL_Texture* continue_;
	GuiButton* Continue_;
	bool continueEnabled;

	SDL_Texture* settings;
	GuiButton* Settings;

	SDL_Texture* credits;
	GuiButton* Credits;

	SDL_Texture* exit;
	GuiButton* Exit;

	SDL_Texture* back;
	GuiButton* Back;

	SDL_Texture* SettingsTitle;
	SDL_Texture* PauseTitle;

	SDL_Texture* slider;
	SDL_Texture* SlideBar;

	SDL_Texture* Music;
	GuiSlider* SliderMusic;

	SDL_Texture* SFX;
	GuiSlider* SliderFX;

	SDL_Texture* framecap;
	SDL_Texture* FPS;
	SDL_Texture* framecapUP;
	GuiButton* FramecapUP;
	SDL_Texture* framecapDOWN;
	GuiButton* FramecapDOWN;

	SDL_Texture* checkBox;

	SDL_Texture* checkBoxFullscreen;
	GuiCheckBox* CheckBoxFullscreen;

	SDL_Texture* checkBoxVsync;
	GuiCheckBox* CheckBoxVsync;

	bool showCredits;
	GuiButton* BackCredits;

	uint OpenPause;
	uint ClosePause;

};