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

	SDL_Texture* Fondo;

	//Pause UI

	SDL_Texture* PauseTitle;

	SDL_Texture* resume;
	GuiButton* Resume;

	SDL_Texture* settings;
	GuiButton* Settings;

	SDL_Texture* backTitle;
	GuiButton* BackTitle;

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

	// Tweens Pause

	int offset = 808;

	Tween Animation_Pause;
	float point_Pause;

	Tween Animation_Resume;
	float point_Resume;

	Tween Animation_BackTitle;
	float point_BackTitle;

	Tween Animation_Settings;
	float point_Settings;

	Tween Animation_Exit;
	float point_Exit;

	// Tweens Settings

	Tween Animation_BigSettings;
	float point_BigSettings;

	Tween Animation_Back;
	float point_Back;
	
};