#pragma once

#include "GuiManager.h"
#include "GuiButton.h"
#include "GuiSlider.h"
#include "GuiCheckBox.h"
#include "Tweening.h"

struct SDL_Texture;

class Pause {
public:

	void Load();

	void Update();

	void PostUpdate();

public:

	bool showPause;
	bool showSettings;

	int offset = 720;
	float point;

	SDL_Texture* Fondo;

	//Pause UI

	SDL_Texture* PauseTitle;

	SDL_Texture* resume;
	GuiButton* Resume;

	SDL_Texture* settings;
	GuiButton* Settings;

	SDL_Texture* backTitle;
	GuiButton* BackTitle;
	Tween Animation_BackTitle;

	SDL_Texture* exit;
	GuiButton* Exit;

	//Settings UI

	SDL_Texture* SettingsTitle;

	SDL_Texture* checkBox;

	SDL_Texture* checkBoxFullscreen;
	GuiCheckBox* CheckBoxFullscreen;

	SDL_Texture* checkBoxVsync;
	GuiCheckBox* CheckBoxVsync;

	SDL_Texture* framecap;
	SDL_Texture* FPS;
	SDL_Texture* framecapUP;
	GuiButton* FramecapUP;
	SDL_Texture* framecapDOWN;
	GuiButton* FramecapDOWN;

	SDL_Texture* slider;
	SDL_Texture* SlideBar;

	SDL_Texture* Music;
	GuiSlider* SliderMusic;

	SDL_Texture* SFX;
	GuiSlider* SliderFX;

	SDL_Texture* back;
	GuiButton* Back;


};